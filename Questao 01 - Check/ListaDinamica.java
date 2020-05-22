
import java.io.BufferedReader;
import java.io.FileReader;
import java.io.IOException;
//import java.io.File;
//import java.util.Scanner;

class Characters {

    // Declaracao de elementos privados
    private String fileName;
    private String name;
    private String height;
    private String weight;
    private String hairColor;
    private String skinColor;
    private String eyeColor;
    private String birthYear;
    private String genre;
    private String homeWorld;

    // Sets and Gets
    public String getFileName() {
        return this.fileName;
    }

    public void setFileName(String fileName) {
        this.fileName = fileName;
    }

    public String getName() {
        return this.name;
    }

    public void setName(String name) {
        this.name = name;
    }

    public String getHeight() {
        return this.height;
    }

    public void setHeight(String height) {
        this.height = height;
    }

    public String getWeight() {
        return this.weight;
    }

    public void setWeight(String weight) {
        this.weight = weight;
    }

    public String getHairColor() {
        return this.hairColor;
    }

    public void setHairColor(String hairColor) {
        this.hairColor = hairColor;
    }

    public String getSkinColor() {
        return this.skinColor;
    }

    public void setSkinColor(String skinColor) {
        this.skinColor = skinColor;
    }

    public String getEyeColor() {
        return this.eyeColor;
    }

    public void setEyeColor(String eyeColor) {
        this.eyeColor = eyeColor;
    }

    public String getBirthYear() {
        return this.birthYear;
    }

    public void setBirthYear(String birthYear) {
        this.birthYear = birthYear;
    }

    public String getGenre() {
        return this.genre;
    }

    public void setGenre(String genre) {
        this.genre = genre;
    }

    public String getHomeWorld() {
        return this.homeWorld;
    }

    public void setHomeWorld(String homeWorld) {
        this.homeWorld = homeWorld;
    }

    Characters() {
        this.fileName = "";
        this.name = "";
        this.height = "";
        this.weight = "";
        this.skinColor = "";
        this.hairColor = "";
        this.eyeColor = "";
        this.birthYear = "";
        this.genre = "";
        this.homeWorld = "";
    }

    // Ler arquivo txt
    public void readCharacter(String fileName) {
        try {
            FileReader arq = new FileReader(fileName);
            BufferedReader readFile = new BufferedReader(arq);
            String line = readFile.readLine();

            // MyIO.println(line);
            // Chamada de funcoes para separar dados
            nameSetUp(line);
            heightSetUp(line);
            massSetUp(line);
            hair_colorSetUp(line);
            skin_colorSetUp(line);
            eye_colorSetUp(line);
            birth_yearSetUp(line);
            genderSetUp(line);
            homeworldSetUp(line);
            readFile.close();
            arq.close();
        } catch (IOException e) {
        }
    }

    // Separar nome
    public void nameSetUp(String line) {

        int nameBegin = line.indexOf("'name'");
        int nameEnd = line.indexOf("'height'", nameBegin);
        String name = line.substring(nameBegin + 7, nameEnd).trim().replace(",", "").replace("'", "");

        this.name = name;
        // MyIO.println("##" + name);
    }

    // Separar altura
    public void heightSetUp(String line) {

        int heightBegin = line.indexOf("'height'");
        int heightEnd = line.indexOf("'mass'", heightBegin);
        String height = line.substring(heightBegin + 10, heightEnd).trim().replace(",", "").replace("'", "")
                .replace("unknown", "0");

        this.height = height;
        // MyIO.println("##" + height);
    }

    // Separar peso
    public void massSetUp(String line) {

        int massBegin = line.indexOf("'mass'");
        int massEnd = line.indexOf("'hair_color'", massBegin);
        String mass = line.substring(massBegin + 8, massEnd).trim().replace(",", "").replace("'", "").replace("unknown",
                "0");

        this.weight = mass;
        // MyIO.println("##" + mass);
    }

    // Separar cor do cabelo
    public void hair_colorSetUp(String line) {

        int hair_colorBegin = line.indexOf("'hair_color'");
        int hair_colorEnd = line.indexOf("'skin_color'", hair_colorBegin);
        String hair_color = line.substring(hair_colorBegin + 14, hair_colorEnd).trim().replace(",", "").replace("'",
                "");

        this.hairColor = hair_color;
        // MyIO.println("##" + hair_color);
    }

    // Separar cor da pele
    public void skin_colorSetUp(String line) {

        int skin_colorBegin = line.indexOf("'skin_color'");
        int skin_colorEnd = line.indexOf("'eye_color'", skin_colorBegin);
        String skin_color = line.substring(skin_colorBegin + 15, skin_colorEnd).trim().replace(",", "").replace("'",
                "");

        this.skinColor = skin_color;
        // MyIO.println("##" + skin_color);
    }

    // Separar cor do olho
    public void eye_colorSetUp(String line) {

        int eye_colorBegin = line.indexOf("'eye_color'");
        int eye_colorEnd = line.indexOf("'birth_year'", eye_colorBegin);
        String eye_color = line.substring(eye_colorBegin + 14, eye_colorEnd).trim().replace(",", "").replace("'", "");

        this.eyeColor = eye_color;
        // MyIO.println("##" + eye_color);
    }

    // Separar ano de nascimento
    public void birth_yearSetUp(String line) {

        int birth_yearBegin = line.indexOf("'birth_year'");
        int birth_yearEnd = line.indexOf("'gender'", birth_yearBegin);
        String birth_year = line.substring(birth_yearBegin + 14, birth_yearEnd).trim().replace(",", "").replace("'",
                "");

        this.birthYear = birth_year;
        // MyIO.println("##" + birth_year);
    }

    // Separar genero
    public void genderSetUp(String line) {

        int genderBegin = line.indexOf("'gender'");
        int genderEnd = line.indexOf("'homeworld'", genderBegin);
        String gender = line.substring(genderBegin + 11, genderEnd).trim().replace(",", "").replace("'", "");

        this.genre = gender;
        // MyIO.println("##" + gender);
    }

    // Separar planeta natal
    public void homeworldSetUp(String line) {

        int homeworldBegin = line.indexOf("'homeworld'");
        int homeworldEnd = line.indexOf("'films'", homeworldBegin);
        String homeworld = line.substring(homeworldBegin + 14, homeworldEnd).trim().replace(",", "").replace("'", "");

        this.homeWorld = homeworld;
        // MyIO.println("##" + homeworld);
    }
}

class Celula {
    public Characters elemento; // Elemento inserido na celula.
    public Celula prox; // Aponta a celula prox.

    public Celula() {
        this(null);
    }

    public Celula(Characters elemento) {
        this.elemento = elemento;
        this.prox = null;
    }
}

class ListaSequencial {

    private Celula primeiro;
    private Celula ultimo;
    // private Characters personagem[];
    // private int contador;

    /**
     * Construtor da classe que cria uma lista sem elementos (somente no cabeca).
     */
    public ListaSequencial() {
        primeiro = new Celula();
        ultimo = primeiro;
        // personagem = new Characters[1000];
        // contador = 0;
    }

    /*
     * public ListaSequencial() { personagem = new Characters[1000]; contador = 0; }
     * 
     * public ListaSequencial(int size) { personagem = new Characters[size];
     * contador = 0; }
     */

    // public int getSize() {
    // return size;
    // }

    // Inserir elemento na primeira posicao da lista
    public void inserirInicio(Characters jedi) {

        Celula tmp = new Celula(jedi);
        tmp.prox = primeiro.prox;
        primeiro.prox = tmp;
        if (primeiro == ultimo) {
            ultimo = tmp;
        }
        tmp = null;
    }

    // Insere elemento na ultima posicao da lista
    public void inserirFinal(Characters jedi) {
        ultimo.prox = new Celula(jedi);
        ultimo = ultimo.prox;
    }

    // Insere um elemento em uma posicao especifica considerando que o
    // primeiro elemento valido esta na posicao 0.
    public void inserir(Characters jedi, int posicao) {

        int tamanho = tamanho();

        // if (posicao < 0 || posicao > tamanho) {
        // throw new Exception("Erro ao inserir posicao (" + posicao + " / tamanho = " +
        // tamanho + ") invalida !");
        if (posicao == 0) {
            inserirInicio(jedi);
        } else if (posicao == tamanho) {
            inserirFinal(jedi);
        } else {
            // Caminhar ate posicao para insercao
            Celula i = primeiro;
            for (int j = 0; j < posicao; j++, i = i.prox)
                ;

            Celula tmp = new Celula(jedi);
            tmp.prox = i.prox;
            i.prox = tmp;
            tmp = i = null;
        }
    }

    public Characters removerInicio() {

        // if (primeiro == ultimo) {
        // throw new Exception("Erro ao remover !");
        // }

        Celula tmp = primeiro;
        primeiro = primeiro.prox;
        Characters resp = primeiro.elemento;
        tmp.prox = null;
        tmp = null;
        return resp;
    }

    public Characters removerFinal() {
        // if (primeiro == ultimo) {
        // throw new Exception("Erro ao remover (vazia)!");
        // }

        // Caminhar ate a penultima celula:
        Celula i;
        for (i = primeiro; i.prox != ultimo; i = i.prox)
            ;

        Characters resp = ultimo.elemento;
        ultimo = i;
        i = ultimo.prox = null;

        return resp;
    }

    public Characters remover(int posicao) {

        Characters resp;
        int tamanho = tamanho();

        // if (primeiro == ultimo) {
        // throw new Exception("Erro ao remover (vazia)!");

        // if (posicao < 0 || posicao >= tamanho) {
        // throw new Exception("Erro ao remover (posicao " + posicao + " / " + tamanho +
        // " invalida!");
        if (posicao == 0) {
            resp = removerInicio();
        } else if (posicao == tamanho - 1) {
            resp = removerFinal();
        } else {
            // Caminhar ate a posicao anterior a insercao
            Celula i = primeiro;
            for (int j = 0; j < posicao; j++, i = i.prox)
                ;

            Celula tmp = i.prox;
            resp = tmp.elemento;
            i.prox = tmp.prox;
            tmp.prox = null;
            i = tmp = null;
        }

        return resp;
    }

    /**
     * Mostra os elementos da lista separados por espacos.
     * 
     * public void mostrar() { int j = 0; for (Celula i = primeiro.prox; i != null;
     * i = i.prox) { MyIO.print("[" + j + "] "); i.elemento.escrever(); } }
     */
    public void mostrar() {
        int j = 0;
        // System.out.print("[ ");
        for (Celula i = primeiro.prox; i != null; i = i.prox, j++) {
            // MyIO.print(i.elemento.getName() + " ");
            MyIO.print("[" + j + "] ## ");
            MyIO.print(i.elemento.getName() + " ## ");
            MyIO.print(i.elemento.getHeight() + " ## ");
            MyIO.print(i.elemento.getWeight() + " ## ");
            MyIO.print(i.elemento.getHairColor() + " ## ");
            MyIO.print(i.elemento.getSkinColor() + " ## ");
            MyIO.print(i.elemento.getEyeColor() + " ## ");
            MyIO.print(i.elemento.getBirthYear() + " ## ");
            MyIO.print(i.elemento.getGenre() + " ## ");
            MyIO.println(i.elemento.getHomeWorld() + " ## ");
        }
        // System.out.println("] ");
    }

    public boolean pesquisar(Characters jedi) {
        boolean resp = false;
        for (Celula i = primeiro.prox; i != null; i = i.prox) {
            if (i.elemento == jedi) {
                resp = true;
                i = ultimo;
            }
        }
        return resp;
    }

    public int tamanho() {
        int tamanho = 0;
        for (Celula i = primeiro; i != ultimo; i = i.prox, tamanho++)
            ;
        return tamanho;
    }

    /*
     * public void escrever() throws Exception { for (int i = 0; i < contador; i++)
     * 
     * { MyIO.print("[" + i + "] ## "); MyIO.print(personagem[i].getName() +
     * " ## "); MyIO.print(personagem[i].getHeight() + " ## ");
     * MyIO.print(personagem[i].getWeight() + " ## ");
     * MyIO.print(personagem[i].getHairColor() + " ## ");
     * MyIO.print(personagem[i].getSkinColor() + " ## ");
     * MyIO.print(personagem[i].getEyeColor() + " ## ");
     * MyIO.print(personagem[i].getBirthYear() + " ## ");
     * MyIO.print(personagem[i].getGenre() + " ## ");
     * MyIO.println(personagem[i].getHomeWorld() + " ## "); } }
     */

    /*
     * public void escrever() throws Exception { Characters[] aux = new
     * Characters[1000]; int contador = 0;
     * 
     * for (Celula i = primeiro; i != ultimo; i = i.prox) { aux[contador] =
     * i.elemento; contador++; }
     * 
     * // aux[contador] = ultimo.elemento; // contador++;
     * 
     * for (int i = 0; i < contador; i++) {
     * 
     * MyIO.print("[" + i + "] ## "); MyIO.print(aux[i].getName() + " ## ");
     * MyIO.print(aux[i].getHeight() + " ## "); MyIO.print(aux[i].getWeight() +
     * " ## "); MyIO.print(aux[i].getHairColor() + " ## ");
     * MyIO.print(aux[i].getSkinColor() + " ## "); MyIO.print(aux[i].getEyeColor() +
     * " ## "); MyIO.print(aux[i].getBirthYear() + " ## ");
     * MyIO.print(aux[i].getGenre() + " ## "); MyIO.println(aux[i].getHomeWorld() +
     * " ## "); } }
     */
}

class ListaDinamica {
    // Identificar palavra FIM
    public static boolean isFIM(String input) {
        return (input.length() >= 3 && input.charAt(0) == 'F' && input.charAt(1) == 'I' && input.charAt(2) == 'M');
    }

    public static String ISO88591toUTF8(String strISO) {
        try {
            byte[] isoBytes = strISO.getBytes("ISO-8859-1");
            return new String(isoBytes, "UTF-8");
        } catch (IOException e) {
        }
        return strISO;
    }

    public static void lerComando(String comando, ListaSequencial list) {

        int posicao = 0;
        Characters character2 = new Characters();
        String comand[] = comando.split(" ");

        switch (comand[0]) {
            case "II":
                character2.readCharacter(comand[1]);
                list.inserirInicio(character2);
                break;
            case "IF":
                character2.readCharacter(comand[1]);
                list.inserirFinal(character2);
                break;
            case "I*":
                posicao = Integer.parseInt(comand[1]);
                character2.readCharacter(comand[2]);
                list.inserir(character2, posicao);
                break;
            case "R*":
                posicao = Integer.parseInt(comand[1]);
                character2 = list.remover(posicao);
                MyIO.println("(R) " + character2.getName());
                break;
            case "RI":
                character2 = list.removerInicio();
                MyIO.println("(R) " + character2.getName());
                break;
            case "RF":
                character2 = list.removerFinal();
                MyIO.println("(R) " + character2.getName());
                break;
        }
    }

    public static void main(String[] args) throws Exception {
        // Inicializacao de lista
        ListaSequencial list = new ListaSequencial();
        // Array de characters
        Characters[] character = new Characters[100];

        String[] input = new String[700];
        int enterNumber = 0;

        MyIO.setCharset("UTF-8");

        // Leitura de dados
        do {
            input[enterNumber] = MyIO.readLine();
            input[enterNumber] = ISO88591toUTF8(input[enterNumber]);
        } while (isFIM(input[enterNumber++]) == false);
        enterNumber--;

        for (int i = 0; i < enterNumber; i++) {
            character[i] = new Characters();
            character[i].readCharacter(input[i]);
            list.inserirFinal(character[i]);
        }
        int size = Integer.parseInt(MyIO.readLine());

        String[] comand = new String[1000];

        for (int i = 0; i < size; i++) {
            comand[i] = MyIO.readLine();
            lerComando(comand[i], list);
        }
        list.mostrar();
    }
}
