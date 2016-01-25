public class Elevador
{
  private int C; // capacidade do elevador
  private Andar andarAtual;
  private Requisicao[] andarDestino; // Array para limitar tamanho e facilitar operações de acesso a cada um dos elementos

  public int getCapacidade () {
    return C;
  }

  public Elevador (Andar aAtual, int capacidadeElevador) {
    andarAtual = aAtual;

    if (C <= 0) throw new CapacidadeNulaOuNegativaException("Capacidade nula ou negativa de carga no elevador");
    C = capacidadeElevador;
  }

  public void rodarFila (Andar andar) {
    // TODO: pegar C elementos da fila do andar e ordena-los para fazer a viagem total mais curta
  }

  // TODO: implementar metodo para levar elevador de um andar a outro
  public void irProximoAndar () {
    andarAtual = andarDestino.remove();
  }
}
