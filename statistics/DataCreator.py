from random import randint

def make_data(): # przekazujemy do c po 100 intow, tutaj mozna sie pobawic w jakies funkcje z random itd.
    for _ in range(100):
        print(randint(-10000, 10000), end=' ')
    print("")

if __name__ == "__main__":
    make_data()