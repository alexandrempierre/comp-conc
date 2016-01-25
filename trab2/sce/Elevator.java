public class Elevator
{
  private int C; // capacidade do elevador
  private Floor currentFloor;
  private Request[] destinations; // Array para limitar tamanho e facilitar operações de acesso a cada um dos elementos
  private int pendingRequests;

  public int getCapacity () {
    return C;
  }

  public Elevator (Floor currentFloor, int elevatorCapacity) {
    this.currentFloor = currentFloor;

    if (C <= 0) throw new ZeroOrNegativeCapacityException("Capacidade nula ou negativa de carga no elevador");
    C = elevatorCapacity;
  }

  public void runQueue (Floor f) {
    // TODO: pegar C elementos da fila do andar e ordena-los para fazer a viagem total mais curta
  }

  // TODO: implementar metodo para levar elevador de um andar a outro
  public void goToNextFloor () {
    currentFloor = destinations.remove();
  }
}
