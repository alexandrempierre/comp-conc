package ufrj.compconc.sce.modelos;

public class Requisicao {

    public final int identificador;
    public final Andar destino;

    public Requisicao (int identificador, Andar destino) {
        this.identificador = identificador;
        this.destino = destino;
    }
}