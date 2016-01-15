public class Vetor {
  protected int[] vetor;
  protected final int tamanho;

  public Vetor (int tamanho) {
    this.tamanho = tamanho;
    this.vetor = new int[this.tamanho];
  }

  public Vetor (int[] valores) {
    this.tamanho = valores.length();
    this.vetor = valores;
  }

  public void imprimir () {
    System.out.println("[ ");

    for (int n: vetor) {
      System.out.println(n + " ");
    }

    System.out.println("]");
  }

  public int tamanhoVetor () {
    return this.tamanho;
  }

  public void definirElemento (int posicao, int valor) {
    try {
      this.vetor[posicao] = valor;
    }
  }

  public void inicializar (int[] valores) {
    this.vetor = valores;
  }

}

public T extends Thread {

  public T () {

  }
}
