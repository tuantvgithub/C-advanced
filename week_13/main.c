#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SPACE 0
#define UP 1
#define DOWN 2
#define LEFT 3
#define RIGHT 4

struct State {
	int a[3][3];
	int i, j;
};

void swap(struct State* s, int i1, int j1, int i2, int j2)
{
	int tmp = s->a[i1][j1];
	
	s->a[i1][j1] = s->a[i2][j2];
	s->a[i2][j2] = tmp;
	
	return;
}

void print_state(struct State s)
{
	for(int i = 0; i < 3; i++) {	
		for(int j = 0; j < 3; j++) {
			printf("%d ", s.a[i][j]);
		}
		printf("\n");
	}

	return;
}

void copy(struct State* s1, struct State* s2)
{
	for(int i = 0; i < 3; i++) {
		for(int j = 0; j < 3; j++) {
			s2->a[i][j] = s1->a[i][j];
		}
	}
	s2->i = s1->i;
	s2->j = s1->j;

	return;
}

int di_chuyen_space(struct State* s, int direc, struct State* new_state)
{
	copy(s, new_state);
	switch(direc) {
		case UP:
			if(new_state->i - 1 > 2 || new_state->i - 1 < 0)
				return 0;
			swap(new_state, new_state->i, new_state->j, new_state->i - 1, new_state->j);
			new_state->i -= 1;	
			break;
		case DOWN:
			if(new_state->i + 1 > 2 || new_state->i + 1 < 0)
				return 0;
			swap(new_state, new_state->i, new_state->j, new_state->i+1, new_state->j);
			new_state->i += 1;
			break;
		case LEFT:
			if(new_state->j - 1 > 2 || new_state->j - 1 < 0)
				return 0;
			swap(new_state, new_state->i, new_state->j, new_state->i, new_state->j-1);
			new_state->j -= 1;
			break;
		case RIGHT:
			if(new_state->j + 1 > 2 || new_state->j + 1 < 0)
				return 0;
			swap(new_state, new_state->i, new_state->j, new_state->i, new_state->j+1);
			new_state->j += 1;
			break;
		default:
			return 0; // error
	}

	return 1;
}

int finish(struct State s1, struct State s2)
{
	int i = 0, j = 0;

	for(; i < 3 && j < 3 && s1.a[i][j] == s2.a[i][j]; i++, j++);

	return i < 3 ? 0 : 1;
}

int visited(struct State s, struct State closed[], int n)
{
	for(int i = 0; i < n; i++) {
		if(finish(s, closed[i])) return 1;
	}

	return 0;
}
	
void arr_copy(int arr1[3][3], int arr2[3][3])
{
	for(int i = 0; i < 3; i++) {	
		for(int j = 0; j < 3; j++) {
			arr2[i][j] = arr1[i][j];
		}	
	}

	return;
}

int main(int argc, char** argv)
{
	struct State open[100], closed[100];
	struct State start, end;
	int path[100] = {0};

	int a_[3][3] = {{1, 2, 3}, {4, 5, 6}, {7, 8, SPACE}};
	int b_[3][3] = {{3, 2, 1}, {4, SPACE, 5}, {7, 8, 6}};

	arr_copy(a_, start.a);
	start.i = start.j = 2;
	arr_copy(b_, end.a);
	end.i = end.j = 1;

	int tail = 0, closed_index = 0;
	int head = 0;
	open[tail++] = start;

	struct State X;
	while(tail > 0) {
		copy(&open[head], &X);

		if(finish(X, end)) {
			print_state(X);
			break;
		} else {
			print_state(X);
			printf("\n");
			closed[closed_index++] = X;
			head += 1; // remove leftmost state from open

			for(int n = 1; n <= 4; n++) {
				struct State new_state;
				if(di_chuyen_space(&X, n, &new_state) == 0) continue;
				if(!visited(new_state, closed, closed_index)) {
					open[(tail) % 100] = new_state;	
					tail += 1;
				}
			}
		}
	}

	return 0;
}
