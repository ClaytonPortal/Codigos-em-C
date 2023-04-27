import java.util.Scanner;

class numeropi extends Thread{
    private final int n; // numero de termos
    private final int nThreads; // número de threads
    private final int threadID; // id da thread
    private double total = 0; // valor calculado de cada thread

    // construtor
    public numeropi(int nTermos, int nThreads, int idThreads){
        this.n = nTermos;
        this.nThreads = nThreads;
        this.threadID = idThreads;
    }

    public void run(){
        for (int i = threadID; i < n; i+=nThreads) {
            this.total += Math.pow((-1), i) * (1.0 / (2 * i + 1));
        }
    }

    // retorna o valor que a thread calculou
    public double getTotal(){
        return this.total;
    }
}

class calc_pi{
    static public int N; // número de threads
    static public int n; // número de termos
    static double soma = 0; // soma dos valores calculados pelas threads
    static double erro; // erro da aproximação
    static double pi = Math.PI; // valor de pi do Java
    static double tol = Math.pow(10.0, (-10.0));

    public static void main(String[] args) {

        // pegando os dados do teclado (n threads, n termos)
        Scanner leitura = new Scanner(System.in);

        System.out.println("Digite o número de Threads:");
        N = leitura.nextInt();
        System.out.println("Digite o número de termos para calcular PI:");
        n = leitura.nextInt();

        // vetor de threads
        Thread[] threads = new Thread[N];

        // criando as threads e armazenando no vetor de threads
        for (int i = 0; i < threads.length; i++) {
            threads[i] = new numeropi(n, N, i);
        }

        // iniciando as threads
        for (int i = 0; i < threads.length; i++) {
            threads[i].start();
        }

        // esperando todas as threads terminarem
        for (int i = 0; i < threads.length; i++) {
            try {
                threads[i].join();
            } catch (InterruptedException e) {
                return;
            }
        }

        // somando todos os totais calculados pelas threads
        for (int i = 0; i < threads.length; i++) {
            numeropi t = (numeropi) threads[i];
            soma += t.getTotal();
        }

        // soma total e erro
        soma = soma * 4;
        erro = Math.abs(pi - soma) / pi;

        // prints
        System.out.println("PI original: " + pi);
        System.out.println("Aproximacao: " + soma);
        System.out.println("Erro relativo: " + erro);

        if (erro <= tol) System.out.println("Erro abaixo da tolerância");
        else System.out.println("Erro acima da tolerância");

        leitura.close();

    }
}
