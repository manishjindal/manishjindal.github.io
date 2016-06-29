package HDFSPackage;
import HDFSPackage.RequestResponse.*;

import java.io.BufferedReader;
import java.io.BufferedWriter;
import java.io.File;
import java.io.FileInputStream;
import java.io.FileReader;
import java.io.FileWriter;
import java.io.IOException;
import java.rmi.Remote;
import java.rmi.registry.LocateRegistry;
import java.rmi.registry.Registry;
import java.rmi.server.UnicastRemoteObject;
import java.security.AllPermission;
import java.util.ArrayList;
import java.util.HashMap;
import java.util.HashSet;
import java.util.Random;
import java.util.Scanner;
import java.util.Set;

import javax.sound.sampled.DataLine;


public class INameNodeServer implements INameNode {

	
	 HashMap<String, ArrayList<Integer>> nameToBlocks = new HashMap <String,ArrayList<Integer>> ();
	 HashMap<Integer, String> handleToname = new HashMap <Integer,String> ();
	 HashMap<Integer, ArrayList<DataNodeLocation>> blockToNodes = new HashMap <Integer,ArrayList<DataNodeLocation>>();
	 HashMap<Integer,DataNodeLocation> aliveDataNodes = new HashMap<Integer,DataNodeLocation>();
	  
	 static int fileHandle = 0;
	 static int blockNumber = 25;   // Initialise from config
	 int replicatioFactor = 3;		// Initialise from config
	 long thresholdTime = 200;
	
	@Override
	public byte[] openFile(byte[] input) {   //OpenFileResponse
		// TODO Auto-generated method stub
		OpenFileRequest openFileRequest = new OpenFileRequest(input);
		OpenFileResponse  openFileResponse = new OpenFileResponse();
				
		if(openFileRequest.forRead == true){     //read request
			if(nameToBlocks.containsKey(openFileRequest.fileName)){   //file exists     
				fileHandle++;
				handleToname.put(fileHandle,openFileRequest.fileName);
				openFileResponse.status = 1;
				openFileResponse.handle = fileHandle;
				openFileResponse.blockNums = (ArrayList<Integer>) nameToBlocks.get(openFileRequest.fileName);
			}else{			// file not exists		
				openFileResponse.status = -1;
				openFileResponse.handle = -1;
				
			}
		}else{				//write request
			fileHandle++;
			handleToname.put(fileHandle,openFileRequest.fileName);
			openFileResponse.handle = fileHandle;
			
			/**
			 * if we have to create new file every time then we remove
			 */
			if(nameToBlocks.containsKey(openFileRequest.fileName)){   //file exists     
				openFileResponse.status = 1;
				openFileResponse.blockNums = (ArrayList<Integer>) nameToBlocks.get(openFileRequest.fileName);
			}else{			// file does not exist.
				ArrayList<Integer> block = new ArrayList<Integer>();
				nameToBlocks.put(openFileRequest.fileName, block);
				openFileResponse.status = 2;
							
			}
		}
		return openFileResponse.toProto();
	}

	@Override
	public byte[] closeFile(byte[] input) { //CloseFileRequest
		// TODO Auto-generated method stub
		
		CloseFileRequest closeFileRequest = new CloseFileRequest(input);
		CloseFileResponse closeFileResponse = new CloseFileResponse();
		if(handleToname.containsKey(closeFileRequest.handle)){			
			closeFileResponse.status = 1;
			handleToname.remove(closeFileRequest.handle);     
		}else{					
			closeFileResponse.status = -1;
		}
		return closeFileResponse.toProto();
	}

	@Override
	public byte[] getBlockLocations(byte[] input) { //BlockLocationRequest
		// TODO Auto-generated method stub
		BlockLocationRequest blockLocationRequest = new BlockLocationRequest(input);
		BlockLocationResponse blockReLocationResponse = new BlockLocationResponse();
		blockReLocationResponse.status = 1; 
		
		for( int b : blockLocationRequest.blockNums){
			BlockLocations block = new BlockLocations();
			block.blockNumber = b;
			if(blockToNodes.containsKey(b)){
				block.locations = blockToNodes.get(b);
				blockReLocationResponse.blockLocations.add(block);
			}else
				blockReLocationResponse.status = 0;
		}
		//set status;
		
		return blockReLocationResponse.toProto();
	}

	@Override
	public byte[] assignBlock(byte[] input) {   //AssignBlockRequest 
		// TODO Auto-generated method stub
		
		AssignBlockRequest assignBlockRequest = new AssignBlockRequest(input);
		AssignBlockResponse assignBlockResponse = new AssignBlockResponse();
		
		ArrayList<DataNodeLocation> allNodes = new ArrayList<DataNodeLocation>();
		allNodes.addAll(aliveDataNodes.values());
		Set<DataNodeLocation> node = new HashSet<>();
		
		int size = aliveDataNodes.size();
		Random randomGen = new Random();
		while(node.size() < replicatioFactor){
			int random = randomGen.nextInt(size);
			if(allNodes.get(random).time >= System.currentTimeMillis() - thresholdTime){
				node.add(allNodes.get(random));
			}
		}
		/**
		 * Code to update nameToBlock mapping
		 */
		blockNumber++;
		ArrayList <Integer> blockList = new ArrayList<Integer>();
		String file = handleToname.get(assignBlockRequest.handle);
		if(nameToBlocks.containsKey(file)){
			blockList = nameToBlocks.get(file);
		}
		blockList.add(blockNumber);	
		nameToBlocks.put(file,blockList);	
		
		try {
			FileWriter fw = new FileWriter(file,true);
			BufferedWriter bw = new BufferedWriter(fw);
			String data = Integer.toString(blockNumber) + ",";
			bw.append(data);
			bw.flush();
			bw.close();
		} catch (IOException e) {
			// TODO Auto-generated catch block
			
			e.printStackTrace();
		}
		
		assignBlockResponse.newBlock.blockNumber = blockNumber;
		assignBlockResponse.newBlock.locations = allNodes;
		assignBlockResponse.status = 1 ;  
		
		return assignBlockResponse.toProto();
	}

	@Override
	public byte[] list(byte[] input) {  //ListFilesRequest
		// TODO Auto-generated method stub
		ListFilesRequest listFileRequest = new ListFilesRequest(input);
		ListFilesResponse listFilesResponse = new ListFilesResponse();
		
		listFilesResponse.status = 1;
		Set<String> list = nameToBlocks.keySet();
		listFilesResponse.fileNames = new ArrayList<String>(list); 
		return listFilesResponse.toProto();
	}

	@Override
	public byte[] blockReport(byte[] input) {	//BlockLocationRequest 
		// TODO Auto-generated method stub
		BlockReportRequest blockReportRequest = new BlockReportRequest(input);
		BlockReportResponse blockReportResponse = new BlockReportResponse();
	
		ArrayList <DataNodeLocation> dataNode;
		for(int b : blockReportRequest.blockNumbers){
			if(blockToNodes.containsKey(b)){
				dataNode = blockToNodes.get(b); 
				if(!(dataNode.contains(blockReportRequest.location))) {
					System.out.println(b);
					dataNode.add(blockReportRequest.location);
					blockToNodes.put(b,dataNode);
				}
			}else{
				dataNode = new ArrayList<DataNodeLocation>(); 
				dataNode.add(blockReportRequest.location);
				blockToNodes.put(b, dataNode);
			}
			blockReportResponse.status.add(1);
		}
		return blockReportResponse.toProto();
	}

	@Override
	public byte[] heartBeat(byte[] input) {		//HeartBeatRequest
 		// TODO Auto-generated method stub
		
		HeartBeatRequest heartBeatRequest = new HeartBeatRequest(input);
		HeartBeatResponse heartBeatResponse = new HeartBeatResponse();
		DataNodeLocation dataNodeLocation = aliveDataNodes.get(heartBeatRequest.id);
		dataNodeLocation.time = System.currentTimeMillis();
		aliveDataNodes.put(heartBeatRequest.id, dataNodeLocation);
		heartBeatResponse.status = 1;
		return heartBeatResponse.toProto();
	}

	public INameNodeServer(String file){
		try {
			FileInputStream  fi = new FileInputStream(file);
			Scanner sc = new Scanner(fi);
			replicatioFactor = sc.nextInt();
			thresholdTime = sc.nextLong();
			blockNumber = sc.nextInt();
			// TODO load nameToBlock
			sc.close();
		} catch (IOException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
		
		
	}
	
	public static void main(String args[]){
		try {
            String name = "NameNode";
            INameNode nameNode = new INameNodeServer(args[0]);
            INameNode stub =
            		(INameNode) UnicastRemoteObject.exportObject((Remote) nameNode, 0);
            Registry registry = LocateRegistry.getRegistry();
            registry.rebind(name, (Remote) stub);
            System.out.println("NameNode bound");
        } catch (Exception e) {
           
            e.printStackTrace();
        }
	}
}
