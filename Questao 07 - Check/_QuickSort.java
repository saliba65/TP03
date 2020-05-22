
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

class CelulaDupla {
    public Characters elemento; // Elemento inserido na celula.
    public CelulaDupla ant, prox; // Aponta a celula prox.

    public CelulaDupla() {
        // this.elemento = new Characters();
        this.ant = this.prox = null;
    }

    public CelulaDupla(Characters elemento) {
        this.elemento = elemento;
        this.ant = this.prox = null;
    }
}

class ListaSequencial {

    private CelulaDupla primeiro;
    private CelulaDupla ultimo;
    // private Characters personagem[];
    // private int contador;

    /**
     * Construtor da classe que cria uma lista sem elementos (somente no cabeca).
     */
    public ListaSequencial() {
        primeiro = new CelulaDupla();
        ultimo = primeiro;
        // personagem = new Characters[1000];
        // contador = 0;
    }

    // Insere elemento na ultima posicao da lista
    public void inserirFinal(Characters jedi) {
        ultimo.prox = new CelulaDupla(jedi);
        ultimo.prox.ant = ultimo;
        ultimo = ultimo.prox;
    }

    public void quickSort() {
        quickSort(primeiro.prox, ultimo);
    }

    private void quickSort(CelulaDupla esq, CelulaDupla dir) {
        CelulaDupla temp1 = esq;
        CelulaDupla temp2 = dir;
        int j = posicao(esq);
        int k = posicao(dir);
        CelulaDupla pivo = primeiro.prox;

        for (int i = 0; i < (j + k) / 2; i++, pivo = pivo.prox)
            ;

        while (j <= k) {
            while (compareTo(temp1.elemento.getHairColor(), pivo.elemento.getHairColor(), temp1.elemento.getName(),
                    pivo.elemento.getName()) < 0) {
                temp1 = temp1.prox;
                j++;
            }

            while (compareTo(temp2.elemento.getHairColor(), pivo.elemento.getHairColor(), temp2.elemento.getName(),
                    pivo.elemento.getName()) > 0) {
                temp2 = temp2.ant;
                k--;
            }

            if (j <= k) {
                swap(getCelulaDupla(j), getCelulaDupla(k));

                j++;
                k--;
            }

            if (posicao(esq) < k) {
                quickSort(esq, getCelulaDupla(k));
            }

            if (j < posicao(dir)) {
                quickSort(getCelulaDupla(j), dir);
            }
        }
    }

    int compareTo(String cabelo1, String cabelo2, String nome1, String nome2) {

        if (cabelo1.compareTo(cabelo2) == 0) {
            return nome1.compareTo(nome2);
        } else {
            return cabelo1.compareTo(cabelo2);
        }
    }

    public int posicao(CelulaDupla celula) {
        int pos = 0;

        for (CelulaDupla i = primeiro.prox; i != celula; i = i.prox, pos++)
            ;

        return pos;
    }

    public CelulaDupla getCelulaDupla(int pos) {
        CelulaDupla celula = primeiro.prox;

        for (int i = 0; i < pos; i++, celula = celula.prox)
            ;

        return celula;
    }

    public void swap(CelulaDupla celula1, CelulaDupla celula2) {
        CelulaDupla aux = new CelulaDupla(celula1.elemento);

        celula1.elemento = celula2.elemento;
        celula2.elemento = aux.elemento;
        aux = null;
    }

    public void mostrar() {
        int j = 0;
        // System.out.print("[ ");
        for (CelulaDupla i = primeiro.prox.prox.prox.prox; i != null; i = i.prox, j++) {
            // MyIO.print(i.elemento.getName() + " ");
            // MyIO.print("[" + j + "] ## ");
            MyIO.print(" ## " + i.elemento.getName() + " ## ");
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
        for (CelulaDupla i = primeiro.prox; i != null; i = i.prox) {
            if (i.elemento == jedi) {
                resp = true;
                i = ultimo;
            }
        }
        return resp;
    }

    public int tamanho() {
        int tamanho = 0;
        for (CelulaDupla i = primeiro; i != ultimo; i = i.prox, tamanho++)
            ;
        return tamanho;
    }

}

class _QuickSort {
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

        list.quickSort();
        list.mostrar();
    }
}
