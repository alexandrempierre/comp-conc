package ufrj.compconc.sce.controladores;

import ufrj.compconc.sce.modelos.*;

/**
 * Created by alexandre on 12/02/16.
 */
public class ControladorElevadores {
    public static Andar[] andares;

    public static Andar proximoAndar (Elevador e) {
        Andar atual = e.posicaoAtual();
        int nAndarAtual, distancia, menorDistancia;

        nAndarAtual = numAndar(atual);

        for (int i = 0; i < nAndarAtual; i++) {

        }

        return null;
    }

    public static int numAndar (Andar a) {
        return a.numeroAndar;
    }

}
