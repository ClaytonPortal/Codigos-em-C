from threading import Thread
import math as m
import time

class numeroPi(Thread):
    def __init__(self, nTermos, idThread, nThreads):
        super().__init__()
        self.n = nTermos
        self.nThreads = nThreads
        self.threadID = idThread
        self.total = 0

    def run(self):
        for i in range(self.threadID, self.n, self.nThreads):
            self.total += m.pow((-1), i) * (1 / (2 * i + 1))

    def getTotal(self):
        return self.total

if __name__ == '__main__':
    
    N = int(input("Digite o número de Threads: ")) #Número de threads
    n = int(input("Digite o número de Termos: ")) #Número de termos
    soma = 0
    
    threads = [numeroPi(n, i, N) for i in range(N)]
    start = time.time()
    
    for thread in threads:
        thread.start()

    for thread in threads:
        thread.join()

    for thread in threads:
        soma += thread.getTotal()

    SOMA = soma * 4

    print(f"Valor aproximado de pi: {SOMA}")
    print(f"Tempo de execução: {time.time() - start}")
