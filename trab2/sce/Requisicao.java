public class Requisicao
{
  private int indentificador; //identificador unico da requisicao
  private Andar andarDestino;

  public int getId () {
    return indentificador;
  }

  public Andar getDestino () {
    return andarDestino;
  }

  public Requisicao (int identificador, Andar destino) {
    andarDestino = destino;
    this.indentificador = identificador;
  }
}
