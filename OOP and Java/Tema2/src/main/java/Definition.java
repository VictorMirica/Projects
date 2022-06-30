import java.util.ArrayList;

public class Definition {
    private String dict;
    private String dictType;
    private int year;
    private ArrayList<String> text;

    public String getDict() {
        return dict;
    }

    public String getDictType() {
        return dictType;
    }

    public int getYear() {
        return year;
    }

    public ArrayList<String> getText() {
        return text;
    }

    public Definition(String dict, String dictType, int year, ArrayList<String> text) {
        this.dict = dict;
        this.dictType = dictType;
        this.year = year;
        this.text = text;
    }

    @Override
    public String toString() {
        return dictType + ": " +
                "dict='" + dict + '\'' +
                ", year=" + year +
                ", text=" + text +
                '}';
    }
}
