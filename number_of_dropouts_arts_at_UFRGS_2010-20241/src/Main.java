import java.nio.file.Path;
import java.nio.file.Paths;
import java.nio.file.Files;
import java.util.stream.Stream;
import java.io.IOException;

public class Main {
    public static void main(String[] args)
    {
        Path path = Path.of("/home/24280006/Desktop/academic/raw/dadosabertos_graduacao_quantitativo-de-alunos.csv");
        try (Stream<String> fp = Files.lines(path)) {
        fp.forEach(System.out::println);

        } catch(IOException x) {
            System.err.println(x);
        }
    }
}