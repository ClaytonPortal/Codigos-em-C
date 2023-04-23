class numeropi extends Thread{
    private final int n; // numero de termos
    private final int nThreads; //10 threads como exemplo
    private final int threadID; // id das threads
    private double total = 0;

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

    public double getTotal(){
        return this.total;
    }
}

class calc_pi{
    static final int N = 100;
    static public int n = 1000000;
    static double soma = 0;
    static double erro;
    static double pi = Math.PI;

    public static void main(String[] args) {
        Thread[] threads = new Thread[N];

        for(int i = 0; i < threads.length; i++){
            threads[i] = new numeropi(n, N, i);
        }

        for(int i = 0; i < threads.length; i++){
            threads[i].start();
        }

        for (int i = 0; i < threads.length; i++) {
            try { threads[i].join(); }
            catch (InterruptedException e) { return; }
        }

        for(int i = 0; i < threads.length; i++){
            numeropi t = (numeropi) threads[i];
            soma += t.getTotal();
        }
        soma = soma*4;
        erro = Math.abs(pi - soma);

        System.out.println("PI original: " + pi);
        System.out.println("Aproximacao: " + soma);
        System.out.println("Erro:" + erro);
    }
}
