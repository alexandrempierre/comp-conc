package ufrj.compconc.sce;

import ufrj.compconc.sce.controladores.ControladorElevadores;
import ufrj.compconc.sce.modelos.*;

import java.util.Scanner;

public class Main {

    public static void main(String[] args) {
        /* N: numero de andares             (5 <= N <= 100)
         * M: numero de elevadores          (5 <= M <= 20)
         * C: capacidade dos elevadores     (5 <= C <= 20)
         */
        int N, M, C;
        Scanner teclado = new Scanner(System.in);

        N = teclado.nextInt();
        M = teclado.nextInt();
        C = teclado.nextInt();

        // Defino a capacidade de todos os elevadores e inicializo o vetor de Elevadores
        Elevador.capacidade = C;
        Elevador[] elevadores = new Elevador[M];

        // Inicializo os andares
        Andar[] andares = new Andar[N];

        for (int i = 0; i < andares.length; i++)
        {
            andares[i] = new Andar(i);
        }

        ControladorElevadores.andares = andares;

        // Inicializo os elevadores
        for (int i = 0; i < elevadores.length; i++)
        {
            try
            {
                elevadores[i] = new Elevador(andares[teclado.nextInt()]);
            }
            catch (ArrayIndexOutOfBoundsException e) { return; }

            elevadores[i].start();
        }

        // Definir as filas de requisicoes de cada andar
        int id = 0;
        Requisicao[] fila;
        for (int i = 0; i < andares.length; i++)
        {
            fila = new Requisicao[teclado.nextInt()];

            for (int j = 0; j < fila.length; j++)
            {
                try
                {
                    fila[j] = new Requisicao(id++, andares[teclado.nextInt()]);
                }
                catch (ArrayIndexOutOfBoundsException e) { return; }
            }

            andares[i].colocarNaFila(fila);
        }

        // Aguardo o fim da operacao dos elevadores
        for (int i = 0; i < elevadores.length; i++)
        {
            try
            {
                elevadores[i].join();
            }
            catch (InterruptedException e) { e.printStackTrace(); }
        }
    }
}