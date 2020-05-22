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

class Matriz {
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
                j.prox = new Celula();
                j.prox.ant = j;
                j.prox.sup = j.sup.prox;
                j.sup.prox.inf = j.prox;
            }
        }
    }
    // ===============================================================================================

    // Mostrar diagonal principal
    public void diagonalPrincipal() {

        if (this.linha == this.coluna && linha > 0) {
            int cont = 0;
            String out = "";
            for (Celula i = inicio; cont < coluna; i = i.prox) {
                out += i.elemento;
                out += " ";
                cont++;
                if (cont < coluna) {
                    i = i.inf;
                }
            }

            MyIO.println(out.substring(0, out.length() - 1));
        }
    }

    // Mostrar diagonal secundaria
    public void diagonalSecundaria() {

        if (this.linha == this.coluna && linha > 0) {
            Celula i = inicio;

            for (; i.prox != null; i = i.prox)
                ;

            int cont = 0;

            String out = "";
            for (; cont < coluna; i = i.ant) {
                out += i.elemento;
                out += " ";
                cont++;
                if (cont < coluna) {
                    i = i.inf;
                }
            }

            MyIO.println(out.substring(0, out.length() - 1));
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
    public Matriz multiplicacao(Matriz a) {
        Matriz resp = null;

        if (this.coluna == a.linha) {
            resp = new Matriz(this.linha, a.coluna);
            Celula i = resp.inicio;
            for (int l = 0; i != null; i = i.inf, l++) {
                Celula i2 = i;
                for (int c = 0; i2 != null; i2 = i2.prox, c++) {
                    i2.elemento = 0;

                    for (int x = 0; x < linha; x++) {
                        i2.elemento += getElemento(l, x) * a.getElemento(x, c);
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

        String out;
        for (Celula i = inicio; i != null; i = i.inf) {
            out = "";

            Celula i2 = i;

            out += i2.elemento;
            for (i2 = i2.prox; i2 != null; i2 = i2.prox) {
                out += " ";
                out += i2.elemento;
            }
            MyIO.println(out);
        }
    }
}

class Principal {
    public static void main(String[] args) {

        int tamanho = Integer.parseInt(MyIO.readLine());

        int linha = 0;
        int coluna = 0;
        String[] comando = new String[1000];

        for (int i = 0; i < tamanho; i++) {
            linha = Integer.parseInt(MyIO.readLine());
            coluna = Integer.parseInt(MyIO.readLine());

            Matriz matriz = new Matriz(linha, coluna);

            for (int c = 0; c < linha; c++)
                matriz.inserir(c, MyIO.readLine());

            linha = Integer.parseInt(MyIO.readLine());
            coluna = Integer.parseInt(MyIO.readLine());

            Matriz matriz2 = new Matriz(linha, coluna);

            for (int c = 0; c < linha; c++)
                matriz2.inserir(c, MyIO.readLine());

            matriz.diagonalPrincipal();
            matriz.diagonalSecundaria();

            Matriz matriz3 = matriz.soma(matriz2);
            matriz3.mostrar();

            matriz3 = matriz.multiplicacao(matriz2);
            matriz3.mostrar();
        }
    }
}