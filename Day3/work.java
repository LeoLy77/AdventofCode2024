import java.io.IOException;
import java.nio.file.Files;
import java.nio.file.Path;
import java.util.stream.Stream;
import java.util.regex.Matcher;
import java.util.regex.Pattern;

class Work {

    private static void part1(Path thePath) {
        final String regex = "mul\\((-?\\d+),\\s*(-?\\d+)\\)";
        Pattern pattern = Pattern.compile(regex);
        Integer sum = 0;
        try(
            Stream<String> lines = Files.lines(thePath);
            Stream<Matcher> matcherStream = lines.map(pattern::matcher)
        ) {
            for(Matcher matcher : (Iterable<Matcher>) matcherStream::iterator) {
                while(matcher.find()) {
                    Integer firstMatch = Integer.parseInt(matcher.group(1));
                    Integer secondMatch = Integer.parseInt(matcher.group(2));
                    sum += firstMatch * secondMatch; 
                }
            } 
        } catch (IOException e) {
            System.err.println(String.format("Sad: %s", e.toString()));
        }

        System.out.println(String.format("Part1: Sum = %d", sum));
    }

    private static void part2(Path thePath){
        final String regex = "mul\\((-?\\d+),\\s*(-?\\d+)\\)|do\\(\\)|don't\\(\\)";

        Pattern pattern = Pattern.compile(regex);
        Integer sum = 0;
        Boolean doSum = true;
        
        try(
            Stream<String> lines = Files.lines(thePath);
            Stream<Matcher> matcherStream = lines.map(pattern::matcher)
        ) {
            for(Matcher matcher : (Iterable<Matcher>) matcherStream::iterator) {
                while(matcher.find()) {
                    String found = matcher.group();
                    if (found.startsWith("don't")) {
                        doSum = false;
                    } else if (found.startsWith("do")) {
                        doSum = true;
                    } 
                    
                    if (found.startsWith("mul") && doSum) {
                        Integer firstMatch = Integer.parseInt(matcher.group(1));
                        Integer secondMatch = Integer.parseInt(matcher.group(2));
                        sum += firstMatch * secondMatch; 
                    }
                }
            } 
        } catch (IOException e) {
            System.err.println(String.format("Sad: %s", e.toString()));
        }

        System.out.println(String.format("Part2: Sum = %d", sum));
    }
    public static void main(String[] args) {
        String filePath = "input.txt";
        Path thePath = Path.of(filePath);
        part1(thePath);
        part2(thePath);
    }
}

