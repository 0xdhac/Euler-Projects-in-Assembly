#include <iostream>

int main(){
	static int total = 0;
	static int counter = 0;
	
	__asm
	{
		call loopstart;
	loopstart:
		push ebp;
		mov ebp, esp;

		inc counter;

		push 3;
		call div_counter_by;
		cmp edx, 0;
		pushfd;
		mov eax, [esp];
		and eax, 0x0040;
		mov [esp], eax;

		push 5;
		call div_counter_by;
		cmp edx, 0;
		pushfd;
		mov eax, [esp];
		and eax, 0x0040;

		mov ebx, [ebp - 0x8];
		or eax, ebx;
		
		cmp eax, 0x0040;
		pop eax;
		pop eax;
		pop eax;
		pop eax;

		je add_to_counter;		

		cmp counter, 1000;
		pop ebp;
		
		jl loopstart;
	restart_loop:
		call loopstart;

	div_counter_by:
		push ebp;
		mov ebp, esp;
		mov edx, 0;
		mov eax, counter;
		mov ecx, [ebp + 8];
		div ecx;
		pop ebp;
		ret;
	add_to_counter:
		mov eax, total;
		add eax, counter;
		mov total, eax;
		cmp counter, 1000;
		jl restart_loop;
	}

	std::cout << total << std::endl;

	total = 0;

	for (int i = 0; i <= 1000; i++) {
		if (i % 3 == 0 || i % 5 == 0) {
			total += i;
		}
	}

	std::cout << total << std::endl;
	std::cin.get();
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
