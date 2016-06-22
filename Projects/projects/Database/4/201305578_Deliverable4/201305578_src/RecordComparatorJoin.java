import java.util.Comparator;

public class RecordComparatorJoin implements Comparator<String> {
	
	public Integer colindex1;
	
	public Integer colindex2;
	
	public String coltype;

	public RecordComparatorJoin(Integer colindex1, Integer colindex2,
		 String coltype) {
		this.colindex1 = colindex1;
		this.colindex2 = colindex2;
		this.coltype = coltype;
		// TODO Auto-generated constructor stub
	}

	@Override
	public int compare(String arg0, String arg1) {
		int comp = compareRecord(arg0, arg1, colindex1, colindex2, coltype);	
		return comp;
	}

	public static int compareRecord(String record1, String record2,
			Integer colindex1, Integer colindex2, String coltype) {
		if(record1==null) {
			return -1;
		}
		if(record2==null) {
			return 1;
		}
		String[] colvalues1 = record1.split(",");
		String[] colvalues2 = record2.split(",");
		//	System.out.println("Colindex "+colindex1);
			String val1 = colvalues1[colindex1].substring(1,
					colvalues1[colindex1].length() - 1);
			String val2 = colvalues2[colindex2].substring(1,
					colvalues2[colindex2].length() - 1);
			if (coltype.equalsIgnoreCase("integer")) {
				int comp = (Integer.valueOf(val1)).compareTo(Integer
						.valueOf(val2));
					return comp;
			} else if (coltype.equalsIgnoreCase("float")) {
				int comp = (Float.valueOf(val1)).compareTo(Float
						.valueOf(val2));
					return comp;
			} else {
				int comp = (colvalues1[colindex1])
						.compareTo(colvalues2[colindex2]);
					return comp;
		}
	}
}