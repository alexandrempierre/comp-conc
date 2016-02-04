import exceptions.NullFloorException;

public class Building
{
  private Floor[] floors;

  public Building (Floor[] floors) {
    this.floors = floors;
  }

  public Building (int floorsQuantity) {
    floors = new Floor[floorsQuantity];
  }

  public void setFloor (int index, Floor f) {
    floors[index] = f;
  }

  public int getFloorsCount () {
    return floors.length;
  }

  public Floor getFloor (int floorNumber) {
    if (floors[floorNumber] == null)
      throw new NullFloorException("Esse andar foi idealizado, mas ainda nao foi feito: instancie o objeto");

    return floors[floorNumber];
  }
}
