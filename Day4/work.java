import java.io.IOException;
import java.nio.file.Files;
import java.nio.file.Path;
import java.util.stream.Stream;
import java.util.ArrayList;
import java.util.List;
import java.util.regex.Matcher;
import java.util.regex.Pattern;


class Work {

    List<String> arr;

    private Boolean loadInput(String filePath) {
        List<String> arr = new ArrayList<>();
        Path thePath = Path.of(filePath);

        try (
            Stream<String> linesStream = Files.lines(thePath)
        ) {
            linesStream.forEach(x -> {
                arr.add(x);
            });

        } catch (IOException e) {
            System.err.println(String.format("Sad: %s", e.toString()));
            return false;
        }

        this.arr = arr;

        return true;
    }

    private static List<Integer> getCharPos(String s, char c) {
        List<Integer> Mpos = new ArrayList<>();
        for (int j = 0; j < s.length(); j++) {
            if (s.charAt(j) == c) {
                Mpos.add(j);
            }
        }
        return Mpos;
    }

    public static int countOccurrencesRegex(String str, String substring) {
        Pattern pattern = Pattern.compile(Pattern.quote(substring));
        Matcher matcher = pattern.matcher(str);

        int count = 0;
        while (matcher.find()) {
            count++;
        }

        return count;
    }

    private char getCharInArr(Integer a, Integer b) {
        try {
            return this.arr.get(a).charAt(b);
        } catch (IndexOutOfBoundsException e) {
            return '0';
        }
    }

    private Integer checkXMAS(Integer currentRow, List<Integer> Mpos) {
        Integer foundCnt = 0;
        String row = this.arr.get(currentRow);

        foundCnt += countOccurrencesRegex(row, "XMAS");
        foundCnt += countOccurrencesRegex(row, "SAMX");
        String formed;
        for (Integer p : Mpos) {
            //Vertical
            char[] car = {getCharInArr(currentRow - 1, p), getCharInArr(currentRow + 1, p), getCharInArr(currentRow + 2, p)};
            formed = String.valueOf(car);
            if (formed.equals("XAS")) {
                foundCnt += 1;
            }

            char[] carf = {getCharInArr(currentRow - 2, p), getCharInArr(currentRow - 1, p), getCharInArr(currentRow + 1, p)};
            formed = String.valueOf(carf);
            if (formed.equals("SAX")) {
                foundCnt += 1;
            }
            
            //Diagonal \
            char[] darb = {getCharInArr(currentRow - 2, p - 2), getCharInArr(currentRow - 1, p - 1), getCharInArr(currentRow + 1, p + 1)};
            formed = String.valueOf(darb);
            if (formed.equals("SAX")) {
                foundCnt += 1;
            }    

            char[] darf = {getCharInArr(currentRow - 1, p - 1), getCharInArr(currentRow + 1, p + 1), getCharInArr(currentRow + 2, p + 2)};
            formed = String.valueOf(darf);
            if (formed.equals("XAS")) {
                foundCnt += 1;
            }    
            
            //Diagonal /
            char[] darb1 = {getCharInArr(currentRow - 2, p + 2), getCharInArr(currentRow - 1, p + 1), getCharInArr(currentRow + 1, p - 1)};
            formed = String.valueOf(darb1);
            if (formed.equals("SAX")) {
                foundCnt += 1;
            }    
    
            char[] darf1 = {getCharInArr(currentRow - 1, p + 1), getCharInArr(currentRow + 1, p - 1), getCharInArr(currentRow + 2, p - 2)};
            formed = String.valueOf(darf1);
            if (formed.equals("XAS")) {
                foundCnt += 1;
            }    
        }

        return foundCnt;
    }

    private void part1(List<String> arr) {
        Integer cumRes = 0;
        for (int i = 0; i < arr.size(); i++) {
            String s = arr.get(i);
            List<Integer> Mpos = getCharPos(s, 'M');
            cumRes += checkXMAS(i, Mpos);
        }

        System.out.println("Result = " + cumRes);
    }

    private Integer checkMASinX(Integer currentRow, List<Integer> Apos) {
        Integer foundCnt = 0;
        String formed;
        for (Integer p : Apos) {
            char[] cars = {getCharInArr(currentRow - 1, p - 1), getCharInArr(currentRow - 1, p + 1), getCharInArr(currentRow + 1, p - 1), getCharInArr(currentRow + 1, p + 1)};
            formed = String.valueOf(cars);
            if (formed.equals("MSMS") || formed.equals("SMSM") || formed.equals("SSMM") || formed.equals("MMSS")) {
                foundCnt += 1;
            }    
        }
        return foundCnt;
    }

    private void part2(List<String> arr) {
        Integer cumRes = 0;
        for (int i = 0; i < arr.size(); i++) {
            String s = arr.get(i);
            List<Integer> Apos = getCharPos(s, 'A');
            cumRes += checkMASinX(i, Apos);
        }

        System.out.println("Result = " + cumRes);
    }

    public void main(String[] args) {
        String filePath = "input.txt";

        loadInput(filePath);
        // part1(arr);
        part2(arr);
    }
}