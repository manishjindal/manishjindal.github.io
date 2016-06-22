import gudusoft.gsqlparser.nodes.TColumnDefinitionList;
import gudusoft.gsqlparser.nodes.TExpression;
import gudusoft.gsqlparser.stmt.TCreateTableSqlStatement;

import java.io.BufferedReader;
import java.io.BufferedWriter;
import java.io.File;
import java.io.FileNotFoundException;
import java.io.FileOutputStream;
import java.io.FileReader;
import java.io.FileWriter;
import java.io.IOException;
import java.util.ArrayList;
import java.util.Collections;
import java.util.HashMap;
import java.util.HashSet;
import java.util.Iterator;
import java.util.List;
import java.util.Map;
import java.util.Map.Entry;
import java.util.Set;
import java.util.TreeMap;

public class DBTools {

	public static List<String> logicalOperators = new ArrayList<String>();
	public static List<String> airthmeticOperators = new ArrayList<String>();
	public static HashMap<String, HashMap<String, String>> allentries = new HashMap<String, HashMap<String, String>>();

	public static HashMap<String, Integer> opcodes = new HashMap<String, Integer>();
	public static HashMap<String, List<String>> tablecolumn = new HashMap<String, List<String>>();

	public static String filein = DBConfig.pathforData + "/" + "temp1.txt";
	public static String fileout = DBConfig.pathforData + "/" + "temp2.txt";
	public static String tempfile = DBConfig.pathforData + "/" + "sublist";

	public static String getSublistfilename(String table, int count) {

		StringBuffer sb = new StringBuffer();
		sb.append(DBConfig.pathforData);
		sb.append("/");
		sb.append(table);
		sb.append("_");
		sb.append("sublist");
		sb.append(count);
		sb.append(".txt");
		return sb.toString();
	}

	public static String getsortedfilename(String table) {

		StringBuffer sb = new StringBuffer();
		sb.append(DBConfig.pathforData);
		sb.append("/");
		sb.append(table);
		sb.append("_");
		sb.append("final");
		sb.append(".txt");
		return sb.toString();
	}

	static {
		// 0 --> = 1 --> > 2 --> >= 3 --> < 4 --> <= 5 --> !=
		opcodes.put("=", 0);
		opcodes.put(">", 1);
		opcodes.put(">=", 2);
		opcodes.put("<", 3);
		opcodes.put("<=", 4);
		opcodes.put("!=", 5);
		opcodes.put("LIKE", 1);
		opcodes.put("like", 1);
	}

	public static HashMap getAllEntries(String filepath) {
		HashMap<String, String> columnmap;
		List<String> columns;
		try {
			FileReader fr = new FileReader(filepath);
			BufferedReader bfr = new BufferedReader(fr);
			// BufferedReader reader = new BufferedReader(new
			// FileReader("/path/to/file.txt"));
			String line = null;
			while ((line = bfr.readLine()) != null) {

				if (line.compareToIgnoreCase("begin") == 0) {
					String tablename = bfr.readLine();
					line = bfr.readLine();

					// System.out.println("line="+line);
					columnmap = new HashMap<String, String>();
					columns = new ArrayList<String>();
					while (line.compareToIgnoreCase("end") != 0) {
						String column[] = line.split(",");
						// String
						// columntype=line.substring(line.indexOf(',')+1,line.length());
						if (column[0].equalsIgnoreCase("PRIMARY_KEY")) {
							break;
						}
						columnmap.put(column[0], column[1]);
						columns.add(column[0]);
						line = bfr.readLine();
						// System.out.println("--line--"+line);
					}
					tablecolumn.put(tablename, columns);
					// System.out.println(tablename+" Table columns "+columnmap);
					allentries.put(tablename, columnmap);
					// columnmap.clear();
				}

			}
			Set<String> tables = tablecolumn.keySet();
			for (String table : tables) {
				List<String> allcolumns = tablecolumn.get(table);
				for (String column : allcolumns) {
					DBIndexing.createIndex(table, column);
				}
			}

		} catch (Exception e) {
			e.printStackTrace();
		}
		return allentries;

	}

	static {
		logicalOperators.add("AND");
		logicalOperators.add("OR");
		logicalOperators.add("and");
		logicalOperators.add("or");
		// <, >, >=, <=, ==, <>
		airthmeticOperators.add("<=");
		airthmeticOperators.add(">=");
		airthmeticOperators.add("<>");
		airthmeticOperators.add("==");
		airthmeticOperators.add(">");
		airthmeticOperators.add("<");
		airthmeticOperators.add("LIKE");
		airthmeticOperators.add("like");

	}

	static DBLru lru = new DBLru();

	public static PageInfo retrievePageInfo(String tableName, int recordId) {
		TreeMap<Integer, PageInfo> mapPageInfo = DBInit.tablemapping
				.get(tableName);
		PageInfo pi = getPageInfo(mapPageInfo, recordId);
		return pi;
	}

	/**
	 * To get the id of the Page from the record id
	 * 
	 * @param mapPageInfo
	 * @param recordid
	 * @return
	 */
	public static PageInfo getPageInfo(TreeMap<Integer, PageInfo> mapPageInfo,
			int recordid) {
		// //System.out.println("FInding "+recordid);
		PageInfo pi = new PageInfo();
		for (Map.Entry<Integer, PageInfo> entry : mapPageInfo.entrySet()) {
			pi = entry.getValue();
			// //System.out.println("Looking in "+pi);
			// //System.out.println("Start at "+pi.getStartrecordid());
			// //System.out.println("End at "+pi.getEndrecordid());

			if ((recordid >= pi.getStartrecordid())
					&& (recordid <= pi.getEndrecordid())) {
				// //System.out.println("Found "+recordid+ " at "+pi);
				return pi;
			}
		}
		return pi;
	}

	public static String getRecord(String tablename, PageInfo pi, int recordid) {
		String tablepage = tablename + "_" + pi.getPageno();
		if (pi.isInmemory()) {
			lru.updatePageintoMemory(tablename, pi.getPageno(), true);
		} else {
			lru.addPageintoMemory(tablename, pi, false, true);
		}
		String record = lru.getRecordFromPageInMemory(tablepage, recordid);
		// System.out.println("Record " + record);
		return record;
	}

	public static File getTableFile(String tablename, String filetype) {
		StringBuffer filepath = new StringBuffer();
		filepath.append(DBConfig.pathforData);
		filepath.append(File.separator);
		filepath.append(tablename);
		if (filetype.equals(DBOutput.CSV)) {
			filepath.append(DBConfig.tablefileextcsv);
		} else {
			filepath.append(DBConfig.tablefileextdata);
		}
		File dbfile = new File(filepath.toString());
		return dbfile;
	}
	
	/*
	public static void checkOrderOfJoin(List<String> joinattribute)
	{
		
		System.out.println(joinattribute);
		HashMap<String,ArrayList<String>>hm=new HashMap<String,ArrayList<String>>();
		for(int i=0;i<joinattribute.size();i++)
		{
			String str[]=joinattribute.get(i).split("[.]");
			ArrayList<String> al=new ArrayList<String>();
			al=hm.get(str[1]);
			if(al.size()!=0)
				al.add(str[0]);
			
			hm.put(str[1],al);	
		}
		
		for (Map.Entry<String, ArrayList<String>> entry : hm.entrySet()) {
				String key = entry.getKey();
				ArrayList<String>value=entry.getValue();
				System.out.println("key="+key);
				System.out.println("value="+value);
		}
	}	
		*/
	/*
	for(int i=0;i<joinattribute.size();i++)
		{
			String out=joinattribute.get(i);
			String outbreak[]=out.split(".");
			
			for(int j=0;j<joinattribute.size();j++)
			{
				
			}
			
		}
	}
	
	*/


	public static void insertRecord(String tablename, String record) {
		
		//Deliverable 4 changes
		
		List<String>columnname;
		columnname=DBTools.tablecolumn.get(tablename);
		int listsize=columnname.size();
		String breakstr[]=record.split(",");

		HashMap<String, HashSet<String>> hm=new HashMap<String, HashSet<String>>();
		HashSet<String>hs=new HashSet<String>();
		hm=DBInit.tablecoldistinctvalues.get(tablename);
//		hs=hm.get(attributeName);
		
		System.out.println(hm);
		
		for(int i=0;i<listsize;i++)
		{
				hs=hm.get(columnname.get(i));
				hs.add(breakstr[i]);
		}
		

		
		
		PageInfo pi = getLastPage(tablename);
		addRecordtoTableFile(tablename, record);
		if (lru.isSpaceinPage(pi, record)) {
			if (pi.isInmemory()) {
				lru.updatePageintoMemory(tablename, pi.getPageno(), false);
			} else {
				lru.addPageintoMemory(tablename, pi, false, false);
			}
			lru.addRecordtoMemPage(tablename, pi, record, false);
		} else {
			PageInfo newpi = lru.addNewPage(tablename);
			lru.addPageintoMemory(tablename, newpi, true, false);
			lru.addRecordtoMemPage(tablename, newpi, record, true);
		}
	}

	public static void addRecordtoTableFile(String tablename, String record) {
		try {

			FileOutputStream fos = new FileOutputStream(getTableFile(tablename,
					DBOutput.CSV), true);
			byte[] b = record.getBytes();
			fos.write(b, 0, record.length());
			fos.write('\n');
			fos.close();
		} catch (Exception e) {
			e.printStackTrace();
		}
	}

	public static PageInfo getLastPage(String tablename) {

		TreeMap<Integer, PageInfo> inner = new TreeMap<Integer, PageInfo>();
		PageInfo pi = null;
		if (DBInit.tablemapping.containsKey(tablename)) {
			inner = DBInit.tablemapping.get(tablename);
			pi = inner.get(inner.lastKey());
		}

		return pi;
	}

	public static boolean isTablesExist(List<String> tables) {
		int flag = 0;
		for (int i = 0; i < tables.size(); i++) {
			String str = tables.get(i);
			if (!isTableExist(str)) {
				// System.out.println("--1-------");
				flag = 1;
				break;
			}
		}

		if (flag == 1)
			return false;
		else
			return true;

	}

	public static boolean isAmbiguous(List<String> tables, List<String> columns) {

		HashMap<String, Integer> alltablecolumn = new HashMap<String, Integer>();
		Map<String, String> columnpertable = new HashMap<String, String>();
		for (int i = 0; i < tables.size(); i++) {
			columnpertable = getDistinctColumn(tables.get(i));
			for (Map.Entry<String, String> entry : columnpertable.entrySet()) {
				String key = entry.getKey();
				// Object value = entry.getValue();
				// ...
				if (alltablecolumn.containsKey(key)) {
					int j;
					j = alltablecolumn.get(key);
					j = j + 1;
					alltablecolumn.put(key, j);
				} else
					alltablecolumn.put(key, 1);
			}
		}

		for (String str : columns) {
			if (alltablecolumn.containsKey(str)) {
				int val;
				val = alltablecolumn.get(str);
				if (val > 1) {
					// System.out.println("Ambi");
					return true;
				}
			}
		}

		return false;

	}

	public static boolean isValidColumns(List<String> tables,
			List<String> columns) {
		if (columns.size() > 0 && columns.get(0).equals("*")) {
			return true;
		}
		// System.out.println("columns to check "+columns);
		HashSet<String> alltablecolumn = new HashSet<String>();
		Map<String, String> columnpertable = new HashMap<String, String>();
		for (int i = 0; i < tables.size(); i++) {
			columnpertable = getColumn(tables.get(i));
			for (Map.Entry<String, String> entry : columnpertable.entrySet()) {
				String key = entry.getKey();
				// Object value = entry.getValue();
				// ...
				alltablecolumn.add(key);
			}
		}

		// System.out.println("Check in "+alltablecolumn);

		if (alltablecolumn.containsAll(columns))
			return true;

		return false;
	}

	public static boolean isValidColumnsType(List<String> tables,
			HashMap<String, String> colvalues, HashMap<String, String> colops) {

		// System.out.println("Is valid column values "+colvalues);
		// System.out.println("Is valid column ops "+colops);

		HashMap<String, String> columnsType = getAllColumsType(tables);
		// System.out.println("Types "+columnsType);
		List<String> allcolumns = getAllTableColumn(tables);
		Set<String> columns = colvalues.keySet();
		for (String column : columns) {
			String columntype = columnsType.get(column);
			String colvalue = colvalues.get(column);
			// System.out.println("All columns "+allcolumns);
			if (allcolumns.contains(colvalues.get(column))) {
				// System.out.println("column on both sides");
				if (!iscomparableColumns(tables, column, colvalue)) {
					return false;
				}
			} else if (columntype.equalsIgnoreCase("Integer")) {
				// System.out.println("column for integer");

				if (!checkInteger(colvalues.get(column), colops.get(column))) {
					// System.out.println("Invalid Integer Type");
					return false;
				}
			} else if (columntype.equalsIgnoreCase("Float")) {
				// System.out.println("column for float");
				if (!checkFloat(colvalues.get(column), colops.get(column))) {
					// System.out.println("Invalid Float Type");
					return false;
				}
			} else if (columntype.startsWith("VARCHAR")
					|| columntype.startsWith("varchar")) {
				// System.out.println("column for varchar");
				if (!checkString(colvalues.get(column))) {
					// System.out.println("Invalid String Type");
					return false;
				}
			}
		}

		return true;
	}

	public static HashMap<String, String> extractColumnValuePair(String where) {
		for (String op : DBTools.logicalOperators) {
			where = where.replace(op, ",");
		}
		where = where.replaceAll("\\s+", "");
		for (String op : DBTools.airthmeticOperators) {
			where = where.replace(op, ":");
		}
		String[] comp = where.split(",");
		HashMap<String, String> colvalue = new HashMap<String, String>();
		for (int i = 0; i < comp.length; i++) {
			String[] split = where.split(":");
			colvalue.put(split[0], split[1]);
		}
		return colvalue;
	}

	public static HashMap<String, String> extractColumnValuePair(
			TExpression where) {

		where.getLeftOperand();
		where.getRightOperand();
		where.getBetweenOperand();

		return null;

	}

	public static boolean checkInteger(String value, String op) {
		if (value == null) {
			return true;
		}
		try {
			Integer.parseInt(value);
		} catch (NumberFormatException e) {
			return false;
		}
		if (op.equalsIgnoreCase("like")) {
			return false;
		}
		return true;
	}

	public static boolean checkFloat(String value, String op) {
		if (value == null) {
			return true;
		}
		try {
			Float.parseFloat(value);
		} catch (NumberFormatException e) {
			return false;
		}
		if (op.equalsIgnoreCase("like")) {
			return false;
		}
		return true;
	}

	public static boolean checkString(String value) {
		if (value == null) {
			return true;
		}
		int len = value.length();
		if (value.charAt(0) == '\'' && value.charAt(len - 1) == '\'') {
			return true;
		}
		if (value.charAt(0) == '\"' && value.charAt(len - 1) == '\"') {
			return true;
		}
		return false;
	}

	public static void createFile(TCreateTableSqlStatement stmt) {
		HashMap<String, String> hm = new HashMap<String, String>();
		try {
			String file = DBConfig.pathforConfig;
			// System.out.println(file);
			FileWriter out = new FileWriter(file, true);
			BufferedWriter bfr = new BufferedWriter(out);

			String tablename = stmt.tables.toString();
			File f = DBTools.getTableFile(tablename, DBOutput.CSV);
			// System.out.println("File f "+f.getAbsolutePath());
			f.createNewFile();
			// -----------Datafile----------
			File f1 = DBTools.getTableFile(tablename, DBOutput.DATA);
			FileWriter f2 = new FileWriter(f1);
			BufferedWriter bfr1 = new BufferedWriter(f2);

			bfr.append("BEGIN");
			bfr.newLine();

			bfr.append(stmt.tables.toString());
			bfr.newLine();

			TColumnDefinitionList tcdl = stmt.getColumnList();
			System.out.print("Attributes:");
			for (int i = 0; i < tcdl.size(); i++) {
				String str = tcdl.elementAt(i).toString();
				str = str.replaceAll("\\s+", " ");
				String str1[] = str.split("[' ']");
				System.out.print(str1[0] + " ");
				bfr1.append(str1[0] + ":");

				hm.put(str1[0], str1[1]);
				if (i == tcdl.size() - 1) {
					bfr1.append(str1[1]);
					System.out.print(str1[1]);
				} else {
					bfr1.append(str1[1] + ",");
					System.out.print(str1[1] + ",");

				}
				bfr.append(str1[0] + "," + str1[1]);
				bfr.newLine();

			}
			// System.out.println();
			allentries.put(stmt.tables.toString(), hm);

			bfr.append("END");
			bfr.newLine();
			bfr.close();
			out.close();
			bfr1.close();
			// System.out.println("File created");
		} catch (Exception e) {
			e.printStackTrace();
		}
	}

	public static boolean isTableExist(String tablename) {
		File tablefile = getTableFile(tablename, DBOutput.CSV);
		// =new File(tablename);
		// System.out.println(tablefile.getAbsolutePath());
		if (tablefile.exists())
			return true;
		else
			return false;

	}

	public static HashMap getAllColumsType(List<String> tables) {
		HashMap<String, String> columntype = new HashMap<String, String>();
		HashMap<String, String> localcolumn = new HashMap<String, String>();

		for (int i = 0; i < tables.size(); i++) {
			localcolumn = getColumn(tables.get(i));
			for (Map.Entry<String, String> entry : localcolumn.entrySet()) {
				String key = entry.getKey();
				String value = entry.getValue();
				columntype.put(key, value);
			}
			localcolumn.clear();

		}

		return columntype;
	}

	public static HashMap<String, String> getColumn(String tablename) {
		HashMap<String, String> columnmap = new HashMap<String, String>();
		HashMap<String, String> columnmaplocal = new HashMap<String, String>();

		columnmap = allentries.get(tablename);

		for (Entry<String, String> in : columnmap.entrySet()) {
			String key1 = in.getKey();
			String val1 = in.getValue();
			// System.out.println("Key1="+key1);
			// System.out.println("Val1="+val1);
			// ...
			columnmaplocal.put(tablename + "." + key1, val1);
		}

		columnmaplocal.putAll(columnmap);

		return columnmaplocal;
	}
	
	public static Map<String, Integer> getAllColumnIndex(String tablename) {
		List<String> columns = tablecolumn.get(tablename);
	//	System.out.println("columns"+columns);
		Map<String, Integer> mapcolumnindex = new HashMap<String, Integer>();
		for(int i=0;i<columns.size();i++) {
			mapcolumnindex.put(columns.get(i), i);
		}
		for(int i=0;i<columns.size();i++) {
			mapcolumnindex.put(tablename+"."+columns.get(i), i);
		}
		return mapcolumnindex;
	}

	public static List<String> getAllTableColumn(List<String> tables) {
		List<String> alltablecolumns = new ArrayList<String>();
		for (String table : tables) {
			alltablecolumns.addAll(DBTools.getColumn(table).keySet());
		}
		return alltablecolumns;
	}

	public static HashMap<String, String> getDistinctColumn(String tablename) {
		HashMap<String, String> columnmap = new HashMap<String, String>();
		columnmap = allentries.get(tablename);
		/*
		 * try { File tablefile = getTableFile(tablename, DBOutput.DATA);
		 * FileReader fr = new FileReader(tablefile); BufferedReader bfr = new
		 * BufferedReader(fr); String str = bfr.readLine(); String[] str1 =
		 * str.split("[,]"); for (int i = 0; i < str1.length; i++) { String[]
		 * str2 = str1[i].split("[:]"); columnmap.put(str2[0], str2[1]);
		 * //columnmap.put(tablename + "." + str2[0], str2[1]); } return
		 * columnmap;
		 * 
		 * } catch (Exception e) { e.printStackTrace(); }
		 */
		return columnmap;
	}

	public static List getAllColumns(List<String> tables) {
		HashSet<String> columntype = new HashSet<String>();
		HashMap<String, String> localcolumn = new HashMap<String, String>();

		for (int i = 0; i < tables.size(); i++) {
			localcolumn.putAll(getDistinctColumn(tables.get(i)));
			for (Map.Entry<String, String> entry : localcolumn.entrySet()) {
				String key = entry.getKey();
				// String value = entry.getValue();
				columntype.add(key);
			}
			localcolumn.clear();

		}
		List<String> listcolumns = new ArrayList<String>();
		listcolumns.addAll(columntype);
		return listcolumns;
	}

	public static boolean iscomparableColumns(List<String> tables,
			String column1, String column2) {
		Map<String, String> columntype = getAllColumsType(tables);
		String type1 = columntype.get(column1);
		String type2 = columntype.get(column2);
		if (type1.equalsIgnoreCase(type2)) {
			return true;
		} else if ((type1.startsWith("varchar") || type1.startsWith("VARCHAR"))
				&& (type2.startsWith("varchar") || type2.startsWith("VARCHAR"))) {
			return true;
		}
		return false;
	}

	public static int getColumnno(String table, String column) {
		//System.out.println("Table "+table);
		List<String> columns = tablecolumn.get(table);
		//System.out.println("columns " + columns);
		int colindex = columns.indexOf(column);
		if(colindex==-1) {
			String col[] = column.split("\\.");
			if(col.length == 2) {
			colindex = columns.indexOf(col[1]);
			}
		}
		return colindex;
	}

	/**
	 * 1 - and 2 - or
	 * 
	 * @param sq
	 */
	public static void executeSelectQuery(SelectQuery sq) {
		List<String> colvalues = sq.getWherevalues();
		List<String> colops = sq.getWhereops();
		String table = sq.getTables().get(0);
		List<String> cols = sq.getWherecols();
	//	if(sq.getWherecols()!=null) {
	//		cols = sq.getWherecols();
	//	}
		Set<Integer> finalrecords = new HashSet<Integer>();
		Integer querytype = sq.getQuerytype();
		boolean firsttime = true;
		List<String> columns = sq.getColumns();
		int noofcolumns = columns.size();
		if(columns.get(0).equals("*")) {
			columns = tablecolumn.get(sq.getTables().get(0));
			//System.out.println("columns "+columns);
		}
		noofcolumns = columns.size();
		List<Integer> colindex = new ArrayList<Integer>();
		for (int i = 0; i < noofcolumns; i++) {
			int colno = getColumnno(table, columns.get(i));
			colindex.add(colno);
		}
		 StringBuffer columnsb = new StringBuffer();
		for(int i=0;i<noofcolumns;i++) {
			columnsb.append("\"");
			columnsb.append(columns.get(i));
			columnsb.append("\"");
			if(i!=noofcolumns-1) {
				columnsb.append(",");					
			}
		}
		String columnstr = columnsb.toString();
		if (cols==null) {
			finalrecords = DBIndexing.tablerecords.get(table);
		//	System.out.println("table records"+DBIndexing.tablerecords);
		//	System.out.println("final reco"+finalrecords);
		} else {
		for (int i=0;i<cols.size();i++) {
			String col = cols.get(i);
			String val = colvalues.get(i);
			String op = colops.get(i);
			Integer opcode = opcodes.get(op);
			String datatype = allentries.get(table).get(col);
			//System.out.println("data type " + datatype);
			TreeMap colrecords = DBIndexing.loadindexintoMemory(table, col);
			//System.out.println("Col records "+colrecords);
			List<Integer> records = null;
			//System.out.println("Value " + val);
			if (datatype.equalsIgnoreCase("integer")) {
				records = DBIndexing.searchIntegerindex(colrecords,
						Integer.parseInt(val), opcode);
			} else if (datatype.equalsIgnoreCase("float")) {
				records = DBIndexing.searchFloatindex(colrecords,
						Float.parseFloat(val), opcode);
			} else if (datatype.startsWith("varchar")) {
			//	val = val.substring(1, val.length() - 1);
				records = DBIndexing.searchStringindex(colrecords, val, opcode);
				//System.out.println("Col Records " + records);
			}
			//System.out.println("Col Records " + records);
			if (records == null && (querytype == null || querytype == 1)) {
				break;
			}
			if ((querytype == null || querytype == 1) && firsttime) {
				finalrecords.addAll(records);
				firsttime = false;
				continue;
			} else {
				firsttime = false;
			}
			if (querytype == 1) {
				finalrecords.retainAll(records);
			} else if (querytype == 2) {
				finalrecords.addAll(records);
			}

			if (finalrecords.size() == 0) {
				System.out.println(columnstr);
				return;
				//break;
			} 
		}
		}
		if (finalrecords.size() == 0) {
			System.out.println(columnstr);
			return;
			//break;
		} else {
			System.out.println(columnstr);
		}
		List<String> ordercols = sq.getOrderby();
		if (ordercols != null) {
			List<File> tempFiles = new ArrayList<File>();
			int noofordercols = ordercols.size();
			HashMap<Integer, String> coltypes = new HashMap<Integer, String>();
			HashMap<String, String> colnametpye = allentries.get(table);
			List<Integer> ordercolindex = new ArrayList<Integer>();
			for (int i = 0; i < noofordercols; i++) {
				int colno = getColumnno(table, ordercols.get(i));
				ordercolindex.add(colno);
				coltypes.put(colno, colnametpye.get(ordercols.get(i)));
			}
			// System.out.println("Column Types "+coltypes);
			int count = 0;
			long totalmemory = (DBConfig.pagesize) * DBConfig.numofPages;
			long usedmemory = 0;
			List<String> recordValues = new ArrayList<String>();
			for (Integer record : finalrecords) {
				PageInfo pi = DBTools.retrievePageInfo(table, record);
				String recordValue = DBTools.getRecord(table, pi, record);
				int recordsize = recordValue.length();
				if (usedmemory + recordsize <= totalmemory) {
					usedmemory = usedmemory + recordsize;
					// System.out.println("used memory "+usedmemory);
					recordValues.add(recordValue);
				} else {
					// System.out.println("Memory used");
					count++;
					Collections.sort(recordValues, new RecordComparator(
							ordercolindex, coltypes));
					String tempfilepath = tempfile + count + ".txt";
					tempFiles.add(new File(tempfilepath));
					BufferedWriter bw;
					try {
						bw = new BufferedWriter(new FileWriter(tempfilepath));
						for (String recordV : recordValues) {
							bw.write(recordV);
							bw.write("\n");
						}
						bw.close();
						recordValues.clear();
						usedmemory = 0;
					} catch (Exception e) {
						// TODO Auto-generated catch block
						e.printStackTrace();
					}
				}
				// System.out.println("Record " + recordValue);
			}
			if (recordValues.size() > 0) {
				count++;
				Collections.sort(recordValues, new RecordComparator(
						ordercolindex, coltypes));
				String tempfilepath = tempfile + count + ".txt";
				tempFiles.add(new File(tempfilepath));

				BufferedWriter bw;
				try {
					bw = new BufferedWriter(new FileWriter(tempfilepath));
					for (String recordV : recordValues) {
						bw.write(recordV);
						bw.write("\n");
					}
					bw.close();
				} catch (IOException e) {
					// TODO Auto-generated catch block
					e.printStackTrace();
				}
			}
			if (!sq.getColumns().get(0).equals("*")) {
				narraymerge(tempFiles, ordercolindex, coltypes, colindex,
						columnstr, true, false);
			} else {
				narraymerge(tempFiles, ordercolindex, coltypes, colindex,
						columnstr, false, false);
			}
			// System.out.println("Final Records " + finalrecords);
		} else {
			for (Integer record : finalrecords) {
				PageInfo pi = DBTools.retrievePageInfo(table, record);
				String recordValue = DBTools.getRecord(table, pi, record);
				if (!sq.getColumns().get(0).equals("*")) {
					String values[] = recordValue.split(",");
					StringBuffer sb = new StringBuffer();
					for (int i = 0; i < noofcolumns; i++) {
						sb.append(values[colindex.get(i)]);
						if (i != noofcolumns - 1) {
							sb.append(",");
						}
					}
					recordValue = sb.toString();
				}
				//System.out.println(columnstr);
				System.out.println(recordValue);
			}
		}
	}

	public static void merge(File f, List<String> records,
			List<Integer> ordercolumns, HashMap<Integer, String> coltypes) {
		BufferedReader br = null;
		try {
			br = new BufferedReader(new FileReader(f));
		} catch (FileNotFoundException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
		try {
			File outfile = new File(fileout);
			BufferedWriter bw = new BufferedWriter(new FileWriter(outfile,
					false));

			Iterator<String> recordit = records.iterator();
			String line = "";
			String record = recordit.next();
			while (recordit.hasNext()) {
				line = br.readLine();
				if (line == null) {
					break;
				}
				// System.out.println("Line "+line);
				int flag = RecordComparator.compareRecord(record, line,
						ordercolumns, coltypes);
				if (flag < 0) {
					bw.append(record);
					record = recordit.next();
				} else if (flag > 0) {
					bw.append(line);
					line = br.readLine();
					bw.append(record);
					bw.append(line);
					line = br.readLine();
					record = recordit.next();
				}
			}
			while (recordit.hasNext()) {
				record = recordit.next();
				bw.append(record);
				// mapit.next();
			}
			line = br.readLine();
			while (line != null) {
				bw.append(line);
				bw.newLine();
				line = br.readLine();
			}
			bw.close();
			String temp = filein;
			filein = fileout;
			fileout = temp;
		} catch (Exception e) {
			// e.printStackTrace();
		}

	}

	public static void narraymerge(List<File> files, Integer column,
			String coltype, boolean issort) {
		List<Integer> ordercolumns = new ArrayList<Integer>();
		ordercolumns.add(column);
		HashMap<Integer, String> coltypes = new HashMap<Integer, String>();
		coltypes.put(column, coltype);
		narraymerge(files, ordercolumns, coltypes, null, null, false, issort);
	}

	public static void narraymerge(List<File> files,
			List<Integer> ordercolumns, HashMap<Integer, String> coltypes,
			List<Integer> colindex, String columnstr, boolean isnottotal,
			boolean issort) {
		// System.out.println("Merging files.....");
		int nooffiles = files.size();
		String outfilename = null;
		List<BufferedReader> listbr = new ArrayList<BufferedReader>();
		for (int i = 0; i < nooffiles; i++) {
			try {
				outfilename = files.get(0).getName().split("_")[0];
				listbr.add(new BufferedReader(new FileReader(files.get(i))));
			} catch (Exception e) {
				// TODO Auto-generated catch block
				e.printStackTrace();
			}
		}
		try {
			File outfile = new File(DBConfig.pathforData + "/" + outfilename
					+ "_final.txt");
		//	System.out.println("Output file " + outfile.getAbsolutePath());
			BufferedWriter bw = new BufferedWriter(new FileWriter(outfile,
					false));
			List<String> lines = new ArrayList<String>();
			for (BufferedReader br : listbr) {
				lines.add(br.readLine());
			}
			while (!listbr.isEmpty()) {
				String minline = lines.get(0);
				int minindex = 0;
				// System.out.println("lines "+lines);
				for (int i = 1; i < lines.size(); i++) {
					String currentline = lines.get(i);

					// System.out.println("Line size "+lines.size()+" min "+minline+" currentline "+currentline);
					int flag = RecordComparator.compareRecord(minline,
							currentline, ordercolumns, coltypes);
					if (flag > 0) {
						minline = currentline;
						minindex = i;
					}
				}
				List<String> newlines = new ArrayList<String>();
				newlines.addAll(lines);
				newlines.remove(minindex);
				String newline = listbr.get(minindex).readLine();
				newlines.add(minindex, newline);
				List<String> towriteline = new ArrayList<String>();
				towriteline.add(lines.get(minindex));
				for (int i = 1; i < lines.size(); i++) {
					String currentline = lines.get(i);
					int flag = RecordComparator.compareRecord(minline,
							currentline, ordercolumns, coltypes);
					if (flag == 0 && i != minindex) {
						newlines.remove(i);
						newline = listbr.get(i).readLine();
						// if(newline!=null)
						newlines.add(i, newline);
						towriteline.add(lines.get(i));
					}

				}
				for (String linew : towriteline) {
					if (isnottotal) {
						String values[] = linew.split(",");
						StringBuffer sb = new StringBuffer();
						int noofcolumns = colindex.size();
						for (int i = 0; i < noofcolumns; i++) {
							sb.append(values[colindex.get(i)]);
							if (i != noofcolumns - 1) {
								sb.append(",");
							}
						}
						linew = sb.toString();
					}
					if (!issort) {
					//	System.out.println(columnstr);
						System.out.println(linew);
					}
					bw.write(linew);
					bw.write("\n");
				}
				List<String> finallines = new ArrayList<String>();
				List<BufferedReader> newlistbr = new ArrayList<BufferedReader>();
				for (int i = 0; i < newlines.size(); i++) {
					if (!(newlines.get(i) == null)) {
						finallines.add(newlines.get(i));
						newlistbr.add(listbr.get(i));
					}
				}
				// System.out.println("finallines "+newlines);
				lines = finallines;
				listbr = newlistbr;

			}
			bw.close();
		} catch (Exception e) {
			e.printStackTrace();
		}
	}

	public static void sortbasedmergejoin(String table, String column) {
	//	System.out.println("Sort based merge join");
			List<File> tempFiles = new ArrayList<File>();
			HashMap<String, String> colnametpye = allentries.get(table);
			int colno = getColumnno(table, column);
			String columntype = colnametpye.get(column);
			List<String> recordValues = new ArrayList<String>();
			TreeMap<Integer, PageInfo> pageidpageinfo = DBInit.tablemapping
					.get(table);
		//	System.out.println("PAge id info" + pageidpageinfo);
			Set<Integer> pageids = pageidpageinfo.keySet();
			int noofpages = 0;
			int count = 0;
			for (Integer pageid : pageids) {
	//			System.out.println("Page id " + pageid);
				noofpages++;
				PageInfo pi = pageidpageinfo.get(pageid);
				int startrecordid = pi.getStartrecordid();
				int endrecordid = pi.getEndrecordid();
				for (int recordid = startrecordid; recordid <= endrecordid; recordid++) {
					String recordValue = DBTools.getRecord(table, pi, recordid);
					recordValues.add(recordValue);
				}
				if (noofpages >= DBConfig.numofPages) {
					Collections.sort(recordValues, new RecordComparator(colno,
							columntype));
					count++;
					String tempfilepath = getSublistfilename(table, count);
					tempFiles.add(new File(tempfilepath));
					BufferedWriter bw;
					try {
						bw = new BufferedWriter(new FileWriter(tempfilepath));
						for (String recordV : recordValues) {
							bw.write(recordV);
							bw.write("\n");
						}
						bw.close();
						recordValues.clear();
						noofpages = 0;
					} catch (Exception e) {
						// TODO Auto-generated catch block
						e.printStackTrace();
					}
				}
				if(recordValues.size()>0) {
					Collections.sort(recordValues, new RecordComparator(colno,
							columntype));
					count++;
					String tempfilepath = getSublistfilename(table, count);
					tempFiles.add(new File(tempfilepath));
					BufferedWriter bw;
					try {
						bw = new BufferedWriter(new FileWriter(tempfilepath));
						for (String recordV : recordValues) {
							bw.write(recordV);
							bw.write("\n");
						}
						bw.close();
						recordValues.clear();
						noofpages = 0;
					} catch (Exception e) {
						// TODO Auto-generated catch block
						e.printStackTrace();
					}
				}
			}
			narraymerge(tempFiles, colno, columntype, true);
			// System.out.println("Record " + recordValue);
		}


	public static void equimergingjoin(String table1, String col1, String table2, String col2, List<String> columns) {
		//System.out.println("Equi Join "+table1+" "+table2+" col1 "+col1+"col 2"+col2+" List "+columns);
		//System.out.println("Equi Join");
		StringBuffer colstring = new StringBuffer();
		if(!columns.get(0).equals("*")) {
			for(int i=0;i<columns.size();i++) {
			colstring.append("\"");
			colstring.append(columns.get(i));
			colstring.append("\"");
			if(i!=columns.size()-1) {
				colstring.append(",");
			}
			}
		} else {
			List<String> cols1 = tablecolumn.get(table1);
			List<String> cols2 = tablecolumn.get(table2);
			for(int i=0;i<cols1.size();i++) {
				colstring.append(cols1.get(i));
				colstring.append(",");
			}	
			for(int i=0;i<cols2.size();i++) {
				colstring.append(cols2.get(i));
				if(i!=cols2.size()-1) {
					colstring.append(",");
				}
			}
		}
		System.out.println(colstring);
		Map<String, Integer> mapcolumnindex1 =  getAllColumnIndex(table1);
		Map<String, Integer> mapcolumnindex2 =  getAllColumnIndex(table2);
		int noofcol1 = tablecolumn.get(table1).size();
		int noofcol2 = tablecolumn.get(table2).size();
		Map<String, Integer> mapcolindexjoin = new HashMap<String, Integer>();
		//System.out.println("Map 1"+mapcolumnindex1);
		//System.out.println("Map 2"+mapcolumnindex2);
		mapcolindexjoin.putAll(mapcolumnindex1);
		Set<String> tablekeys2 = mapcolumnindex2.keySet();
		for(String column:tablekeys2) {
			mapcolindexjoin.put(column,mapcolumnindex2.get(column)+noofcol1);
		}
		//System.out.println("Merging of two columns "+mapcolindexjoin);
		String outfilename = null;
		int colindex1 = getColumnno(table1, col1);
		int colindex2 = getColumnno(table2, col2);
		HashMap<String, String> colnametpye = allentries.get(table1);
		String coltype = colnametpye.get(col1);
		try {
		BufferedReader br1 = new BufferedReader(new FileReader(
				getsortedfilename(table1)));
		BufferedReader br2 = new BufferedReader(new FileReader(
				getsortedfilename(table2)));
		String record1 = br1.readLine();
		String record2 = br2.readLine();
			while (record1 != null && record2 != null) {
			//	System.out.println("record1"+record1);
			//	System.out.println("record2"+record2);
				int flag  = RecordComparatorJoin.compareRecord(record1, record2,
						colindex1, colindex2, coltype);
				if (flag < 0) {
					record1 = br1.readLine();
			//		System.out.println("record1 < record2");
					continue;
				} else if(flag>0) {
					record2 = br2.readLine();
			//		System.out.println("record1 > record2");
					continue;	
				}
				
				int samerecord1 = 0;
				String newrecord1 = br1.readLine();
				String newrecord2 = br2.readLine();
		//		System.out.println("New record 1 "+newrecord1);
		//		System.out.println("New record 2 "+newrecord2);
				samerecord1 = RecordComparatorJoin.compareRecord(record1,
						newrecord1, colindex1, colindex1, coltype);
				List<String> listsamerecord1 = new ArrayList<String>();
				listsamerecord1.add(record1);
				while (samerecord1 == 0) {
					listsamerecord1.add(newrecord1);
					newrecord1 = br1.readLine();
				//	System.out.println("New record 1 "+newrecord1);
					samerecord1 = RecordComparatorJoin.compareRecord(record1,
							newrecord1, colindex1, colindex1, coltype);
				}
				//System.out.println("list of same record 1"+listsamerecord1);
				int samerecord2 = 0;
				samerecord2 = RecordComparatorJoin.compareRecord(record2,
						newrecord2, colindex2, colindex2, coltype);
				List<String> listsamerecord2 = new ArrayList<String>();
				listsamerecord2.add(record2);
				while (samerecord2 == 0) {
					listsamerecord2.add(newrecord2);
					newrecord2 = br2.readLine();
					samerecord2 = RecordComparatorJoin.compareRecord(record1,
							newrecord2, colindex2, colindex2, coltype);
				}
				StringBuffer sb = new StringBuffer();
				for(String recordtable1: listsamerecord1) {
					sb.append(recordtable1);
					for (String recordtable2 : listsamerecord2) {
						sb.append(",");
						sb.append(recordtable2);
						String temprecord = sb.toString();
								String values[] = temprecord.split(",");
								StringBuffer sbrecord = new StringBuffer();
								if(!columns.get(0).equals("*")) {
								int noofcolumns = columns.size();
								for (int i = 0; i < noofcolumns; i++) {
									int colindex = mapcolindexjoin.get(columns.get(i));
									sbrecord.append(values[colindex]);
									if (i != noofcolumns - 1) {
										sbrecord.append(",");
									}
								}
								} else {
									sbrecord = sb;
								}
								//System.out.println("complete record "+sb.toString());	
								System.out.println(sbrecord.toString());
								sb.setLength(0);
								
							}
					}
				record1 = newrecord1;
				record2 = newrecord2;
			}
		} catch (Exception e) {
			e.printStackTrace();
		}
	}
}
