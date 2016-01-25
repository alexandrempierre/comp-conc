import java.util.Scanner;

public class Lab12 {
  private static int nThreads;

  public static void main(String[] args) {
    Scanner keyboard = new Scanner(System.in); // Objeto que vai receber as entradas do teclado
    int len;

    // Recebe o tamanho dos vetores com que se vai trabalhar
    System.out.println("Digite o tamanho dos vetores: ");
    len = keyboard.nextInt();

    // Instancia os vetores
    Vector A, B, C;
    try {
      A = new Vector(len);
      B = new Vector(len);
      C = new Vector(len);
    } catch (NegativeArraySizeException e) { return; }

    // Inicializa os vetores com valores passados pelo usuário
    System.out.println("Digite os elementos do vetor A: ");
    A.init();

    System.out.println("Digite os elementos do vetor B: ");
    B.init();

    // Trata o caso em que os vetores tiverem tamanho zero
    if (len == 0) {
      C.print();
      return;
    }

    // Define o numero de threads a ser usado
    nThreads = Runtime.getRuntime().availableProcessors();
    nThreads = nThreads > len ? len : nThreads;

    // Instancia um vetor de threads
    Thread[] threads = new Thread[nThreads];

    // Instancia cada elemento do vetor como um objeto da minha subclasse ThreadSum
    for (int i = 0; i < threads.length; i++) {
      threads[i] = new ThreadSum(i, nThreads, A, B, C);
    }

    // Inicia as threads
    for (int i = 0; i< threads.length; i++) {
       threads[i].start();
    }

    // Aguarda o fim das threads
    for (int i = 0; i < threads.length; i++) {
      try { threads[i].join(); } catch (InterruptedException e) { return; }
    }

    // Após garantir que os vetores já foram somados imprime o vetor Soma
    System.out.println("Vetor C:");
    C.print();
  }
}
