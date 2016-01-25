/* Disciplina: Computacao Concorrente */
/* Prof.: Silvana Rossetto */
/* Laboratório: 13 */
/* Codigo: Produtor/consumidor em Java */
/* -------------------------------------------------------------------*/

// Monitor
class Buffer {
  static final int N = 10;    //tamanho do buffer
  int[] buffer = new int[N];  //reserva espaco para o buffer
  int count=0, in=0, out=0;   //variaveis compartilhadas

  // Construtor
  Buffer() {
    for (int i=0;i<N;i++)  buffer[i] = -1;
  } // inicia o buffer

  // Insere um item
  public synchronized void Insere (int item) {
    try {
      while (count == N) wait();

      buffer[in] = item;
      in = (in + 1) % N;
      count++;
      notify();
    } catch (InterruptedException e) { }
  }

  // Remove um item
  public synchronized int[] Remove () {
   int aux[] = new int[N];
   try {
     while (count < N) wait();
     count = 0;

     for (int i = 0; i < N; i++) aux[i] = buffer[i];
      // aux = buffer[out];
      // System.out.println("Item " + aux + " removido da posição " + out);
      // out = (out + 1) % N;
      // count--;
      System.out.println("Buffer consumido");
      notify();
    } catch (InterruptedException e) { return null; }

    return aux;
  }
}

//--------------------------------------------------------
// Consumidor
class Consumidor extends Thread {
  int id;
  int delay;
  Buffer buffer;

  // Construtor
  Consumidor (int id, int delayTime, Buffer b) {
    this.id = id;
    this.delay = delayTime;
    this.buffer = b;
  }

  // Método executado pela thread
  public void run () {
    System.out.println("Consumidor " + id + " rodando");

    int item[];
    try {
      for (;;) {
        item = this.buffer.Remove();
        System.out.println("Consumidor " + id + " removeu");
        sleep(this.delay); //...simula o tempo para fazer algo com o item retirado
      }
    } catch (InterruptedException e) { return; }
  }
}

//--------------------------------------------------------
// Produtor
class Produtor extends Thread {
  int id;
  int delay;
  Buffer buffer;

  // Construtor
  Produtor (int id, int delayTime, Buffer b) {
    this.id = id;
    this.delay = delayTime;
    this.buffer = b;
  }

  // Método executado pelo thread
  public void run () {
    System.out.println("Produtor " + id + " rodando");

    try {
      for (;;) {
        this.buffer.Insere(this.id); //simplificacao: insere o proprio ID
        System.out.println(id + " Inserido no Buffer");
        sleep(this.delay);
      }
    } catch (InterruptedException e) { return; }
  }
}

//--------------------------------------------------------
// Classe principal
class PC {
  static final int P = 5;
  static final int C = 5;

  public static void main (String[] args) {
    int i;
    Buffer buffer = new Buffer();      // Monitor
    System.out.println("Buffer de tamanho " + buffer.N + " instanciado");

    Consumidor[] cons = new Consumidor[C];   // Consumidores
    System.out.println("Vetor de Consumidores inicializado");

    Produtor[] prod = new Produtor[P];       // Produtores
    System.out.println("Vetor de Produtores inicializado");


    for (i=0; i<C; i++) {
       cons[i] = new Consumidor(i+1, 1000, buffer);
       System.out.println("Consumidor " + (i + 1) + " criado");
       cons[i].start();
       System.out.println("Consumidor " + (i + 1) + " iniciado");
    }
    for (i=0; i<P; i++) {
       prod[i] = new Produtor(i+1, 1000, buffer);
       System.out.println("Produtor " + (i + 1) + " criado");
       prod[i].start();
       System.out.println("Produtor " + (i + 1) + " iniciado");
    }
  }
}
