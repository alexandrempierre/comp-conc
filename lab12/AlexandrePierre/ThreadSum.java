public class T extends Thread {
  int tid, nThreads;
  Vector A, B, C;

  public T (int tid, int nThreads, Vector A, Vector B, Vector C) {
    this.A = A;
    this.B = B;
    this.C = C;
    this.tid = tid;
    this.nThreads = nThreads;
  }

  // Soma elementos dos dois vetores em uma determinada posição
  public int sumElementsAt (int index) {
    return A.getElementAt(index) + B.getElementAt(index);
  }

  // Soma todos os elementos dos dois vetores que forem atribuídos a essa thread
  public void run () {
    for (int i = tid; i < A.getLength(); i += nThreads) {
      C.setElementAt(i, sumElementsAt(i));
    }
  }
}
