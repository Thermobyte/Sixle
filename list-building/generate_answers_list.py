from array import array
import os
from numpy.random import choice


def generate_list():
    word_file = open('Sixle/list-building/final-words-list.txt', 'r')
    words_str = word_file.read()
    words_list = words_str.split('\n')

    random_answers_list = choice(words_list, 300)
    answer_file = open('answers-list.txt', 'w')
    for x in random_answers_list:
        answer_file.write(x)
        answer_file.write('\n')

    answer_file.close()
    word_file.close()


def arrayify_answers():
    answer_file = open('Sixle/list-building/answers-list.txt', 'r')
    answers_str = answer_file.read()
    answers_list = answers_str.split('\n')

    array_file = open('answers-array.txt', 'w')
    for x in answers_list:
        array_file.write(f'["{x}"], ')
    answer_file.close()
    array_file.close()


def main():
    arrayify_answers()


if __name__ == "__main__":
    main()