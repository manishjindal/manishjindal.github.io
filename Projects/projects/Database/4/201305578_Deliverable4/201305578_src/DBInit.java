import java.io.BufferedReader;
import java.io.File;
import java.io.FileInputStream;
import java.io.FileNotFoundException;
import java.io.FileReader;
import java.io.IOException;
import java.io.RandomAccessFile;
import java.util.ArrayList;
import java.util.HashMap;
import java.util.HashSet;
import java.util.List;
import java.util.TreeMap;


public class DBInit {

	public static TreeMap<String, TreeMap<Integer, PageInfo>> tablemapping = new TreeMap<String, TreeMap<Integer, PageInfo>>();

	public static HashMap<String, HashMap<String, HashSet<String>>> tablecoldistinctvalues = new HashMap<String, HashMap<String, HashSet<String>>> ();
	public static HashMap<String,Integer>noOfRowsInaTable=new HashMap<String,Integer>();
	public static HashSet<String>hs=new HashSet<>();
	public static void  createtablecoldistinctvalues(List<String> listtablename)
	{
		
		for(String str:listtablename)
		{
			List<String>columnname;
			int count=0;
			columnname=DBTools.tablecolumn.get(str);
			//System.out.println("no of column"+columnname.size());
			int listsize=columnname.size();
			
//			ArrayList<HashSet<Integer>> rows = new ArrayList<HashSet<Integer>>();
			HashSet [] arrcoldistinctvalues =new HashSet[listsize];
			HashMap<String,HashSet<String>>hm=new HashMap<String,HashSet<String>>();
			try
				{
					File fr;
					fr=DBTools.getTableFile(str,"CSV");
					BufferedReader bfr=new BufferedReader(new FileReader(fr));
					String line;
					for(int i=0;i<listsize;i++) {
						arrcoldistinctvalues[i] = new HashSet<String>();
					}
					while((line=bfr.readLine())!=null)
					{
//						//System.out.println("--1--"+line);
						String breakstr[];
						breakstr=line.split(",");
						for(int i=0;i<listsize;i++)
						{
//							//System.out.println("breakstr[i]"+breakstr[i]);
								arrcoldistinctvalues[i].add(breakstr[i]);
								//Thread.sleep(100);
						}
						count++;
					}
					
					for(int i=0;i<listsize;i++)
					{
						hm.put(columnname.get(i),arrcoldistinctvalues[i]);
					}
					tablecoldistinctvalues.put(str,hm);
					noOfRowsInaTable.put(str, count);
//					hm.clear();
				}
			catch(Exception e)
				{
					e.printStackTrace();
				}
		}
	
	}
	public static TreeMap<String, TreeMap<Integer, PageInfo>> createTablesMapping(List<String> listtablename) {
		for(String tablename : listtablename) {
			//////System.out.println("Argument "+listtablename);
			TreeMap<Integer, PageInfo> mappageinfo = createMappingPageinfo(tablename);
		tablemapping.put(tablename, mappageinfo);
		////System.out.println("tablemapping" + tablemapping);
		}
		return tablemapping;
	}
	
	
	public static TreeMap<Integer, PageInfo> createMappingPageinfo(String tablename) {
		File tablefile = DBTools.getTableFile(tablename, DBOutput.CSV);
		TreeMap<Integer, PageInfo> mapPageInfo = new TreeMap<Integer, PageInfo>();
		////System.out.println("path"+tablefile.getAbsolutePath());
		FileInputStream fis = null;
		try {
			 fis = new FileInputStream(tablefile);
		} catch (FileNotFoundException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
		try {
			PageInfo pi = new PageInfo();
			int recordid = -1;
			int currentpagesize = 0;
			int recordlength = 0;
			int pageno = 0;
			int seekpoint = 0;
			pi.setPageno(pageno);
			pi.setStartrecordid(0);
			pi.setBeiginpoint(seekpoint);
				RandomAccessFile raf = new RandomAccessFile(tablefile, "r");
				String recordcontent = "";
				while((recordcontent=raf.readLine())!=null) {
				recordlength = recordcontent.length();
					if(currentpagesize+recordlength < DBConfig.pagesize) {
						
							currentpagesize = currentpagesize + recordlength + 1;
							recordid++;
							//System.out.println("consider newline "+currentpagesize+"-1-"+recordid);
						} else if(currentpagesize+recordlength == DBConfig.pagesize) {
							currentpagesize = currentpagesize + recordlength;
							recordid++;
							//System.out.println(currentpagesize+"-2-"+recordid);
						} else {
							pi.setEndrecordid(recordid);
							pi.setPagesize(currentpagesize);
							pi.setEndpoint(seekpoint);
							mapPageInfo.put(pageno, pi);
							//System.out.println(""+pi);
							pi = new PageInfo();
							pageno++;
							if(recordlength < DBConfig.pagesize) {
							currentpagesize = recordlength + 1;
							//System.out.println(currentpagesize+"-1--"+(recordid+1));
							} else {
								currentpagesize = recordlength;
								//System.out.println(currentpagesize+"---"+(recordid+1));
							}
							pi.setPageno(pageno);
							recordid++;
							pi.setStartrecordid(recordid);
							pi.setBeiginpoint(seekpoint);	
							
				}
					seekpoint = seekpoint+recordlength+1;
					//System.out.println("seekpoint="+seekpoint);
			}
		//	//System.out.println("Record id"+recordid);
			pi.setEndrecordid(recordid);
			pi.setPagesize(currentpagesize);
			pi.setEndpoint(seekpoint);
			mapPageInfo.put(pageno, pi);
		//System.out.println(pageno+" "+pi);
			fis.close();
		} catch (IOException e) {
			e.printStackTrace();
		}
		////System.out.println("Map info" + mapPageInfo);
	return mapPageInfo;
	}
	
}
	
