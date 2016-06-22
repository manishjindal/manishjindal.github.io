import gudusoft.gsqlparser.EDbVendor;
import gudusoft.gsqlparser.TGSqlParser;
import gudusoft.gsqlparser.stmt.TCreateTableSqlStatement;
import gudusoft.gsqlparser.stmt.TSelectSqlStatement;

import java.io.BufferedReader;
import java.io.InputStreamReader;
import java.util.ArrayList;
import java.util.HashMap;
import java.util.HashSet;
import java.util.List;
import java.util.Map;
import java.util.TreeMap;

public class DBSystem {
		
	
	TGSqlParser sqlparser = new TGSqlParser(EDbVendor.dbvoracle);
	
	public static TreeMap<String, TreeMap<Integer, PageInfo>> tablemapping = new TreeMap<String, TreeMap<Integer, PageInfo>>();	
		/*
	public static int V(String tableName, String attributeName)
	{
		int columnno;
		HashSet<String>unique_attribute=new HashSet<String>();
		columnno=DBTools.getColumnno(tableName, attributeName);
		System.out.println("columnno"+columnno);
		try{
			File fr;
			fr=DBTools.getTableFile(tableName,"CSV");
			BufferedReader bfr=new BufferedReader(new FileReader(fr));
			String str;
			while((str=bfr.readLine())!=null)
			{
				String breakstr[];
				breakstr=str.split(",");
				System.out.println("str="+str);
				if(str==null)
					break;
				System.out.println(" ---"+breakstr[columnno]);
				unique_attribute.add(breakstr[columnno]);
				
			}
			System.out.println("toatal"+unique_attribute.size());
			bfr.close();
		}
		catch(Exception e)
		{
			e.printStackTrace();
		}
		
		return 0;
		
	}
	
	*/
	public static int T(String tableName)
	{
//		System.out.println("tablename="+tableName);
		return DBInit.noOfRowsInaTable.get(tableName);
	}
	
	public static int V(String tableName, String attributeName)
	{
		HashMap<String, HashSet<String>> hm=new HashMap<String, HashSet<String>>();
		HashSet<String>hs=new HashSet<String>();
		hm=DBInit.tablecoldistinctvalues.get(tableName);
		hs=hm.get(attributeName);
//		System.out.println("--1--"+tableName);
//		System.out.println("--2--"+attributeName);
		try{
			return hs.size();
		}
		catch(Exception e){
			return 0;
		}
	}
	
	
	

	public static void printOptimalPra(int s[][],int i,int j)
	{
		System.out.println("--------111-----------");
		
		for(int k=i;k<j;k++)
		{
			for(int l=i;l<j;l++)
			{
				System.out.print(s[k][l]+"  ");
				
			}
			System.out.println();
		}
		
	
		if(i==j)
		{
			System.out.println("A"+i);
		}
		else
		{
			System.out.println("(");
			System.out.println("i="+i+"j="+j);
			printOptimalPra(s, i, s[i][j]);
			printOptimalPra(s, s[i][j]+1, j);
			System.out.println(")");
			
		}
	
		
	}
	
	
	public static void matrixChainOrder(ArrayList<String> listitem)
	{
		int j,q = 0;
		int n=listitem.size();
		int m[][]=new int[n][n];
		int s[][]=new int[n][n];
		
		for(int i=0;i<n;i++)
			m[i][i]=0;
		
		for(int l=2;l<n;l++)
		{
			for(int i=1;i<n-l+1;i++)
			{
				j=i+l-1;
				m[i][j]=10000000;
				for(int k=i;k<j-1;k++)
				{
					String out=listitem.get(i);
					String in=listitem.get(k);
			//		System.out.println("out:"+out+"\tin:"+in);
					String out_break[]=out.split("[.]");
					String in_break[]=in.split("[.]");
		//			System.out.println(out_break[0]);
					if(in_break[1].compareToIgnoreCase(out_break[1])==0)
					{
						int ta,tb,va,vb,max;
						ta=T(out_break[0]);
						tb=T(in_break[0]);
						va=V(out_break[0],out_break[1]);
						vb=V(in_break[0],in_break[1]);
						if(va>vb)
							max=va;
						else
							max=vb;
						
						q=(ta*tb)/max;
						
					}
					
					if(q<m[i][j])
					{
						m[i][j]=q;
						s[i][j]=k;
					}
				}
			}
		}
		
		int i=1;
		j=n-187;
		System.out.println("i="+i);
		System.out.println("j="+j);
		
		//System.out.println(n-2);
		System.out.println("COST MATRIX:");
		for(int k=1;k<n;k++)
		{
			for(int l=1;l<n;l++)
			{
				System.out.print(m[k][l]+"  ");
				
			}
			System.out.println();
		}
		System.out.println("PARANTHESIS MATRIX:");
		for(int k=1;k<n;k++)
		{
			for(int l=1;l<n;l++)
			{
				System.out.print(s[k][l]+"  ");
				
			}
			System.out.println();
		}
		
		
		//printOptimalPra(s, i, j);
		
	}
					
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	public static void checkOrderOfJoin(ArrayList<String> joinattribute)
	{
		int size=joinattribute.size();
		TreeMap<Integer,String>tm=new TreeMap<Integer,String>();
		for(int i=0;i<size;i++)
		{
			String out=joinattribute.get(i);
			String out_break[]=out.split("[.]");
			for(int j=i+1;j<size;j++)
			{
				String in=joinattribute.get(j);
				String in_break[]=in.split("[.]");
//				System.out.println("");
//				System.out.println("out="+out);
//				System.out.println("in="+in);
				if(out_break[1].compareToIgnoreCase(in_break[1])==0)
				{
					int ta,tb,va,vb;
//					System.out.println("out_break[0]="+out_break[0]);
//					System.out.println("out_break[0]="+out_break[1]);
					ta=T(out_break[0]);
					tb=T(in_break[0]);
					va=V(out_break[0],out_break[1]);
					vb=V(in_break[0],out_break[1]);
					int max,cost;
					if(va>vb)
						max=va;
					else
						max=vb;
					cost=(ta*tb)/max;
					tm.put(cost,out_break[0]+","+in_break[0]);
				}
			}
		}
		String value=null;
		while(joinattribute.size()!=0)
		{
			int key = 0;
			
			for(Map.Entry<Integer,String> entry : tm.entrySet()) {
				  key = entry.getKey();
				  value = entry.getValue();
				  break;
//				  System.out.println(key + " => " + value);
				}
			tm.clear();
			String value_break[]=value.split(",");
//			System.out.println("--1---"+value);
			for(int i=0;i<value_break.length;i++)
			{
//				joinattribute.remove(joinattribute.contains(value_break[i]));
//				int s=0;
//				s=joinattribute.size();
//				System.out.println("--s--"+s);
				for(int j=0;j<joinattribute.size();j++)
				{
					String str=joinattribute.get(j);
//					System.out.println("--2--"+str);
//					System.out.println("--3--"+value_break[i]);
					if(str.contains(value_break[i]))
					{
//						System.out.println("removing"+str);
						joinattribute.remove(j);
						j--;
					}
				}
			}
			
			for(int i=0;i<joinattribute.size();i++)
			{
				String in=joinattribute.get(i);
//				System.out.println("in="+in);
				String in_break[]=in.split("[.]");
				int ta,tb,va,vb = 0;
				ta=T(in_break[0]);
				tb=key;
				va=V(in_break[0],in_break[1]);
				String val[]=value.split(",");
//				System.out.println("val[0]"+val[0]);
//				System.out.println("--4--"+value);
//				System.out.println("--5--"+val.length);
				for(int j=0;j<val.length;j++)
				{
//					System.out.println("--6--"+j);
//					System.out.println("--3--"+val[j]);
					vb=V(val[j],in_break[1]);
					if(vb!=0)
						break;
				}
				
//				vb=V(out_break[0],out_break[1]);
				int max,cost;
				if(va>vb)
					max=va;
				else
					max=vb;
				cost=(ta*tb)/max;
				tm.put(cost,value+","+in_break[0]);
			}
		}
		String bracket[]=value.split(",");
		for(int i=0;i<bracket.length;i++)
		{
			if(i==0)
				{	System.out.print("((");
					System.out.print(bracket[i]+",");
				}
			if(i>0)
			{
				System.out.print(bracket[i]);
			}
			if(i==(bracket.length-1))
				System.out.print(")");
			else if(i>0)
				System.out.print("),");
				
		}
//		System.out.println("value="+value);
		
	}
	
	public void readConfig(String configFilePath) {
	//	System.out.println("Read config gile "+configFilePath);
		DBConfig.loadConfig(configFilePath);
		DBTools.getAllEntries(configFilePath);
	}

	public static void populateDBInfo() {
		tablemapping = DBInit.createTablesMapping(DBConfig.listtablename);
		DBInit.createtablecoldistinctvalues(DBConfig.listtablename);
	}
	
	


	public static String getRecord(String tableName, int recordId) {
		PageInfo pi = DBTools.retrievePageInfo(tableName, recordId);
		String record = DBTools.getRecord(tableName, pi, recordId);
		return record;
	}
	
	public static void insertRecord(String tableName, String record) {
		DBTools.insertRecord(tableName, record);
	}

	/*
	Deteremine the type of the query (select/create) and
	invoke appropriate method for it.
	*/
	
	void queryType(String query) {
		sqlparser.sqltext = query;
		//System.out.println("Input: "+query);
		int ret = sqlparser.parse();
		if (ret == 0){
		for(int i=0;i<sqlparser.sqlstatements.size();i++){
		//	System.out.println("Output:");
		DBQueryParser.analyzeStmt(sqlparser.sqlstatements.get(i));
	//	System.out.println("");
		}
		}else{
		//	System.out.println("Testing: Exception!!!");
		//	System.out.println("Output:");
		System.out.println("Query Invalid");
		}	
	}

	void createCommand(String query) {
		sqlparser.sqltext = query;
		System.out.println("Input: "+query);
		int ret = sqlparser.parse();
		if (ret == 0){
		for(int i=0;i<sqlparser.sqlstatements.size();i++){
			System.out.println("Output:");
		DBQueryParser.analyzeCreateStmt((TCreateTableSqlStatement)sqlparser.sqlstatements.get(i));
	}
		} else {
			System.out.println("Output:");
			System.out.println("Query Invalid");
		
		}
	}

	/*
	Use any SQL parser to parse the input query. Perform all validations (table
	name, attributes, datatypes, operations). Print the query tokens as specified
	below.
	*/

	void selectCommand(String query) {
		sqlparser.sqltext = query;
		System.out.println("Input: "+query);
		int ret = sqlparser.parse();
		if (ret == 0){
		for(int i=0;i<sqlparser.sqlstatements.size();i++){
			//System.out.println("Output:");
		SelectQuery sq = DBQueryParser.selectCommand((TSelectSqlStatement)sqlparser.sqlstatements.get(i));
		DBTools.executeSelectQuery(sq);
	}
		} else {
			//System.out.println("Output:");
			System.out.println("Query Invalid");
		}
		}

	public static void main(String[] args) {
		String systemconfig = args[0];
	//	String systemconfig = "config.txt";
		DBConfig.pathforConfig = systemconfig;
		//String inputfile = args[1];
		//String inputfile = "data/input.txt";
		//File f = new File(inputfile);
	//	System.out.println(""+f.getAbsolutePath());
	//	System.out.println("input--"+inputfile);
		DBSystem db = new DBSystem();
		db.readConfig(systemconfig);
		populateDBInfo();
	//	System.out.println(" "+DBConfig.pathforData);
	   // System.out.println("Enter Queries");
	/*	ArrayList<String> listtablename=new ArrayList<String>();
		listtablename.add("R");listtablename.add("S");listtablename.add("T");
		listtablename.add("U");
		DBInit.createtablecoldistinctvalues(listtablename);
//		int m,n;
//		m=T("check1");
//		n=V("check1","sid");
//		System.out.println("m="+m+","+n);
		
		HashSet<String >li=new HashSet<String>();
		li.add("R.a");li.add("R.b");
		li.add("S.b");li.add("S.c");
		li.add("T.d");li.add("T.c");
		li.add("U.d");li.add("U.a");
		ArrayList<String> al=new ArrayList<String>();
		al.addAll(li);
		checkOrderOfJoin(al); */
		//System.out.println(V("employee", "empid"));
		//insertRecord("employee", "\"16\",\"topper\",\"3\"");
		//System.out.println(V("employee", "empid"));
		//insertRecord("employee", "\"15\",\"topper\",\"4\"");
		//System.out.println(V("employee", "empid"));
		String sqlquery23 = "select * from employee where deptid>3";
		String sqlquery24 = "select * from R join S ON R.b=S.b Join T ON S.c=T.c Join U ON T.d=U.d ";
		String sqlquery25 = "select employee.empid from employee inner join dept ON employee.deptid=dept.id";
		
	//	for(String sqlquery: myQuery) {
			//System.out.println("Query number");
		//DBQueryParser.testQuery(sqlquery23);
		//	DBQueryParser.testQuery(sqlquery24);
		//	DBQueryParser.testQuery(sqlquery25);
	//	}
		
//			System.out.println(V("S","c"));
//		matrixChainOrder(al);
		
		try {
			BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
			String line = "";
			int nooflines = Integer.parseInt(br.readLine());
			for(int i=0;i<nooflines;i++) {
				line = br.readLine();
			//	System.out.println("executing "+line);
				try {
				db.queryType(line);
				}catch (Exception e) {
					e.printStackTrace();
					continue;
				}
			}
		} catch (Exception e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}	
		
		
	/*	List<String> listtables = new ArrayList<String>();
		listtables.add("student");
		listtables.add("employee");
		listtables.add("dept");
		System.out.println("Hekkllo");
		DBTools.sortbasedmergejoin("student", "cgpa");
		DBTools.sortbasedmergejoin("employee", "deptid");
		DBTools.sortbasedmergejoin("dept", "id");
		List<String> columns = new ArrayList<String>();
		columns.add("empname");
		columns.add("dept.id");
		columns.add("deptname");
		DBTools.equimergingjoin("employee", "deptid", "dept", "id",columns);

		*/
	}
}
