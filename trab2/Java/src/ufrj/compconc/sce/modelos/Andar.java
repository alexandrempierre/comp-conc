package ufrj.compconc.sce.modelos;

import java.util.LinkedList;

public class Andar {
    public final int numeroAndar;
    private LinkedList<Requisicao> fila;

    public Andar (int numeroAndar) {
        this.fila = new LinkedList<>();
        this.numeroAndar = numeroAndar;
    }

    public Requisicao rodarFila () {
        return fila.remove();
    }

    public LinkedList<Requisicao> rodarTodaFila () { return fila; }

    public int tamanhoFila () { return fila.size(); }

    public void colocarNaFila (Requisicao req) { fila.add(req); }

    public void colocarNaFila (Requisicao[] reqs) {
        for (Requisicao r : reqs)
            fila.add(r);
    }

    public void definirFila (LinkedList<Requisicao> fila) { this.fila = fila; }
}