package ufrj.compconc.sce.modelos;

import ufrj.compconc.sce.controladores.ControladorElevadores;

import java.util.LinkedList;

public class Elevador extends Thread {
    public static int capacidade;
    private Andar andarAtual;
    private LinkedList<Requisicao> fila;

    public Elevador (Andar andarAtual) {
        this.fila = new LinkedList<>();
        this.andarAtual = andarAtual;
    }

    private Andar andarRequisicao (Requisicao req) {
        return req.destino;
    }

    private int distanciaAndares (Andar a1, Andar a2) {
        return Math.abs(a1.numeroAndar - a2.numeroAndar);
    }

    // TODO: Lógica de movimentação do elevador vazio
    public Andar proximoDestino () {
        Andar a;

        if (fila.size() == 0) synchronized (this) {
            a = ControladorElevadores.proximoAndar(this);

            return a;
        }

        Andar a1 = andarRequisicao(fila.getFirst());

        int distancia;
        int menorDistancia = distanciaAndares(a1, andarAtual);
        a = a1;

        for (int i = 1; i < fila.size(); i++){
            a1 = andarRequisicao(fila.get(i));
            distancia = distanciaAndares(a1, andarAtual);

            if (distancia < menorDistancia) {
                a = a1;
                menorDistancia = distancia;
            }
        }

        return a;
    }

    public void seguirViagem () {
        andarAtual = proximoDestino();
    }

    public void desembarcarPassageiros () {
        for (int i = 0; i < fila.size(); i++)
            if (andarRequisicao(fila.get(i)) == andarAtual)
                fila.remove(i);
    }

    public void embarcarPassageiros (Andar a) {
        if (a.tamanhoFila() < capacidade) {
            this.fila = a.rodarTodaFila();
            return;
        }

        for (int i = 0; i < capacidade; i++) {
            fila.add(a.rodarFila());
        }
    }

    public Andar posicaoAtual () {
        return andarAtual;
    }

    @Override
    public void run() {

    }
}