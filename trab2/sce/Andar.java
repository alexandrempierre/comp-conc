import java.util.LinkedList; // Estrutura de dados sem tamanho pré-definido que possa facilmente ser utilizada em FIFO

public class Andar
{
  private int numeroAndar; // numero do andar
  private LinkedList<Requisicao> requisicoes; // fila de requisicoes no andar

  public int getNumero () {
    return numeroAndar;
  }

  public LinkedList<Requisicao> fila () {
    return requisicoes;
  }

  public int getTamanhoFila () {
    return requisicoes.size();
  }

  public Requisicao embarcarPessoa () {
    return requisicoes.poll();
  }

  public Andar (int numAndar) {
    if (numAndar < 0)
      throw new QuantidadeNegativaException("Quantidade de andares negativa");

    numeroAndar = numAndar;
  }
}
