// - saliba
class Celula {
    int elemento;
    Celula prox, ant, inf, sup;

    public Celula() {
        this(0);
    }

    public Celula(int elemento) {
        this.elemento = elemento;
        prox = ant = inf = sup = null;
    }
}

public class Matriz {
    int linha, coluna;
    Celula inicio;

    public Matriz() {
        this(3, 3);
    }

    public Matriz(int linha, int coluna) {
        this.linha = linha;
        this.coluna = coluna;
        // int x = 0;

        Celula i, j;
        int lin, col;

        // Criar a primeira celula
        inicio = new Celula();
        // ==========================================================================================
        // Criar as demais (coluna-1) celulas da 1ª linha
        for (j = inicio, col = 1; col < coluna; j = j.prox, col++) {
            j.prox = new Celula();
            j.prox.ant = j;
        }
        // ==========================================================================================
        // Criar as demais (linha-1) linhas
        for (i = inicio, lin = 1; lin < linha; i = i.inf, lin++) {
            i.inf = new Celula();
            i.inf.sup = i;

            for (j = i.inf, col = 1; col < coluna; j = j.prox, col++) {
                j.prox = new Celula(x++);
                j.prox.ant = j;
                j.prox.sup = j.sup.prox;
                j.sup.prox.inf = j.prox;
            }
        }
    }
    // ===============================================================================================

    // Mostrar diagonal principal
    public void diagonalPrincipal() {

        if (this.linha == this.coluna && this.linha > 0) {
            Celula i = inicio;
            do {
                System.out.println(i.elemento);
                i = i.prox;
                if (i != null) {
                    i = i.inf;
                }
            } while (i != null);
        }
    }

    // Mostrar diagonal secundaria
    public void diagonalSecundaria() {

        if (this.linha == this.coluna && linha > 0) {
            Celula i = inicio;
            int contador = 1;

            for (; contador < coluna; i = i.prox) {
                contador++;
            }

            contador = 0;

            for (; contador < coluna; i = i.ant) {
                System.out.println(i.elemento);
                contador++;
                if (contador < coluna) {
                    i = i.inf;
                }
            }
        }
    }

    // chamada metodo soma
    public Matriz soma(Matriz a) {
        return soma(this, a);
    }

    // Metodo soma da matriz
    public Matriz soma(Matriz a, Matriz b) {
        Matriz resp = null;

        if (a.linha == b.linha && a.coluna == b.coluna) {
            resp = new Matriz(a.linha, a.coluna);

            Celula iResp = resp.inicio;
            Celula iA = a.inicio;
            Celula iB = b.inicio;

            for (int i = 0; i < linha; i++) {
                Celula jResp = iResp;
                Celula jA = iA;
                Celula jB = iB;

                for (int j = 0; j < coluna; j++) {
                    jResp.elemento = jA.elemento + jB.elemento;
                    jResp = jResp.prox;
                    jA = jA.prox;
                    jB = jB.prox;
                }
                iResp = iResp.inf;
                iA = iA.inf;
                iB = iB.inf;
            }
        }
        return resp;
    }

    // Metodo multiplicacao da matriz
    public Matriz multiplicacao(Matriz m) {
        Matriz resp = null;

        if (this.coluna == m.linha) {
            resp = new Matriz(this.linha, m.coluna);
            Celula i = resp.inicio;
            for (int l = 0; i != null; i = i.inf, l++) {
                Celula i2 = i;
                for (int c = 0; i2 != null; i2 = i2.prox, c++) {
                    i2.elemento = 0;

                    for (int x = 0; x < linha; x++) {
                        i2.elemento += getElemento(l, x) * m.getElemento(x, c);
                    }
                }
            }

        }

        return resp;
    }

    public int getElemento(int l, int c) {
        Celula i = this.inicio;

        for (int j = 0; j < l; j++, i = i.inf)
            ;

        for (int j = 0; j < c; j++, i = i.prox)
            ;

        return i.elemento;
    }

    public void inserir(int l, String x) {
        String[] array = x.split(" ");

        for (int i = 0; i < coluna; i++) {
            inserir(l, i, Integer.parseInt(array[i]));
        }
    }

    public void inserir(int l, int c, int x) {

        Celula i = inicio;

        for (int j = 0; j < l; j++, i = i.inf)
            ;

        for (int j = 0; j < c; j++, i = i.prox)
            ;

        i.elemento = x;
    }

    // Printar matriz
    public void mostrar() {
        for (Celula i = inicio; i != null; i = i.inf) {
            for (Celula j = i; j != null; j = j.prox) {
                System.out.println("[" + j + "] = " + j.elemento + " -- (prox = " + j.prox + "/ ant = " + j.ant
                        + " / inf = " + j.inf + "/ sup = " + j.sup + ")");
            }
        }
    }
}

class Principal {
    public static void main(String[] args) {
        Matriz a = new Matriz(3, 3);
        a.mostrar();
        a.diagonalPrincipal();
        a.diagonalSecundaria();
        a.soma(a);
        a.multiplicacao(a);
        a.mostrar();
    }
}