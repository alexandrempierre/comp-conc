import java.util.Scanner;

public class Vector {
  private int[] array;
  private int length;

  // Construtor
  public Vector (int len) {
    this.length = len;
    this.array = new int[this.length];
  }

  // Imprime vetor
  public void print () {
    System.out.print("{ ");

    for (int i = 0; i < length; ++i) {
      System.out.print(array[i] + (i != (length - 1) ? "," : "") + " ");
    }

    System.out.println("}");
  }

  // Retorna quantidade de elementos do vetor
  public int getLength () {
    return length;
  }

  // Retorna elemento numa posição do vetor
  public int getElementAt (int index) {
    return array[index];
  }

  // Atribui um determinado valor a um elemento específico do vetor
  public void setElementAt (int index, int value) {
    try {
      array[index] = value;
    }
    catch (ArrayIndexOutOfBoundsException e){ System.out.println("ArrayIndexOutOfBoundsException"); }
  }

  // Inicialização do Vetor através de entrada de teclado
  public void init () {
    Scanner keyboard = new Scanner(System.in);

    for (int i = 0; i < this.length; ++i) {
      array[i] = keyboard.nextInt();
    }
  }

}
