all:
	g++ -o run_create_lists create_lists.cpp

clean:
	rm run_create_lists
	rm updated_words_list.txt
	rm answer_array.txt
	rm allowed_guess_array.txt