import java.io.IOException;
import java.nio.file.Files;
import java.nio.file.Path;
import java.util.stream.Stream;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.List;
import java.util.Map;
import java.util.Set;
import java.util.HashMap;
import java.util.HashSet;
import java.util.stream.Collectors;


class Work {

    List<String> arr;
    Map<Integer, Set<Integer>> rules = new HashMap<>();

    private Boolean loadInput(String filePath) {
        List<String> arr = new ArrayList<>();
        Path thePath = Path.of(filePath);
        Boolean nextInputPart = false;
        try (
            Stream<String> linesStream = Files.lines(thePath)
        ) {
            for (String line : (Iterable<String>) linesStream::iterator) {
                if (line.isEmpty()) {
                    nextInputPart = true;
                }

                if (nextInputPart) {
                    arr.add(line);
                } else {
                    String[] ruleParts = line.split("\\|");
                    int firstNumber = Integer.parseInt(ruleParts[0].trim());
                    int secondNumber = Integer.parseInt(ruleParts[1].trim());

                    this.rules.putIfAbsent(firstNumber, new HashSet<>());
                    this.rules.get(firstNumber).add(secondNumber);
                }
            }

        } catch (IOException e) {
            System.err.println(String.format("Sad: %s", e.toString()));
            return false;
        }

        this.arr = arr;
        return true;
    }

    public static boolean validateArray(List<Integer> array, Map<Integer, Set<Integer>> rules) {
        Map<Integer, Integer> indices = new HashMap<>();
        for (int i = 0; i < array.size(); i++) {
            indices.put(array.get(i), i);
        }
        
        for (Map.Entry<Integer, Set<Integer>> entry : rules.entrySet()) {
            int left = entry.getKey();
            Set<Integer> rights = entry.getValue();
            if (!indices.containsKey(left)) 
                continue; 
            int leftIndex = indices.get(left);
            
            for (int right : rights) {
                if (!indices.containsKey(right)) 
                    continue; 

                if (indices.get(right) < leftIndex) {
                    return false; 
                }
            }
        }
        return true; // All rules satisfied
    }

    private void validatePrint() {
        int sum = 0;
        boolean isGood = false;
        for(String prod : arr) {
            String[] pageNumbersUnadultered = prod.split("\\,");
            List<Integer> pageNumbers = Arrays.stream(pageNumbersUnadultered).filter(s -> !s.isEmpty()).map(Integer::parseInt).collect(Collectors.toList());

            if (pageNumbers.isEmpty()) {
                continue;
            }
            isGood = validateArray(pageNumbers, rules);
            
            // System.out.println(String.format("midIndex = %d", midIndex));
            // System.out.println(pageNumbers);
            if (isGood) {
                int midIndex = Math.floorDiv(pageNumbers.size(), 2);
                sum += pageNumbers.get(midIndex);
            }

        }
        System.out.println(String.format("Sum = %d", sum));
    }
    
    private void validatePrintPart2() {
        int sum = 0;
        boolean isGood = false;
        for(String prod : arr) {
            String[] pageNumbersUnadultered = prod.split("\\,");
            List<Integer> pageNumbers = Arrays.stream(pageNumbersUnadultered).filter(s -> !s.isEmpty()).map(Integer::parseInt).collect(Collectors.toList());

            if (pageNumbers.isEmpty()) {
                continue;
            }
            isGood = validateArray(pageNumbers, rules);

            if (!isGood) {
                
                int midIndex = Math.floorDiv(pageNumbers.size(), 2);
                sum += pageNumbers.get(midIndex);
            }

        }
        System.out.println(String.format("Sum = %d", sum));
    }

    public void main(String[] args) {
        String filePath = "input.txt";

        loadInput(filePath);
        validatePrint();
        validatePrintPart2();
    }
}