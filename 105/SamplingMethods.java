import java.util.Scanner;
import java.util.Random;
import java.util.ArrayList;

public class SamplingMethods {
	Scanner scanner = new Scanner(System.in);
	Random rand = new Random();
	int dataType = 0;

	public static void main(String[] args) {
		SamplingMethods test = new SamplingMethods();
		test.menu();
	}

	public void menu() {
		int choice = 0;
		try {
			do {
				System.out.println("\n\n\n\t\t~~~~Basic Sampling Methods~~~~");
				System.out.println("\n\n\n\t\t1 - Simple Random Sampling");
				System.out.println("\n\t\t2 - Systematic Sampling");
				System.out.println("\n\t\t3 - Stratified Sampling");
				System.out.println("\n\t\t4 - Quit");
				System.out.print("\n\n\n\t\tEnter your choice: ");

				choice = scanner.nextInt();

				switch(choice) {
					case 1:
						random(getpop());
						break;
					case 2:
						systematic(getpop());
						break;
					case 3:
						stratified(getpop());
						break;
					case 4:
						return;
					default:
						break;
				}
			} while(choice < 1 || choice > 4);
			menu();
		} catch(java.util.InputMismatchException e) {
			System.out.println("\t\tNot an integer");
		}
	}

	private ArrayList<String> getpop() {
		int size = 0;
		ArrayList<String> population = new ArrayList<String>();

		try {
			System.out.print("\n\n\t\tEnter size of target population: ");
			size = scanner.nextInt();

			initArray(size, population);
			scanner.nextLine();

			do {
				System.out.print("\n\t\tEnter data #1: ");
				population.set(0, scanner.nextLine());
				if (population.get(0).length() == 0 || getDataType(population.get(0)) == 0)
					System.out.println("\t\tInvalid Input");
			} while(population.get(0).length() == 0 || getDataType(population.get(0)) < 1 || getDataType(population.get(0)) > 2);

			for(int i = 1; i < size; i ++) {
				do {
					System.out.print("\t\tEnter data #" + (i+1) + ": ");
					population.set(i, scanner.nextLine());
					if(population.get(i).length() == 0 || !validate(population.get(i)))
						System.out.println("\t\tInvalid Input");
				} while(population.get(i).length() == 0 || !validate(population.get(i)));
			}

			display("THE SAMPLING FRAME", population);
		} catch(java.util.InputMismatchException e) {
			System.out.println("\t\tNot an integer");
		}

		return population;
	}

	public void display(String title, ArrayList<String> population) {
		System.out.print("\n\n" + title);
		
		for(int i = 0; i < population.size(); i += 5) {
			System.out.print("\n");

			for(int j = i; j < i+5 && j < population.size(); j ++) {
				System.out.print("Index " + (j+1) + "\t");

				if(j < 10)
					System.out.print("\t");
			}

			System.out.print("\n");

			for(int j = i; j < i+5 && j < population.size(); j ++) {
				System.out.print(population.get(j) + "\t");

				if(population.get(j).length() < 8)
					System.out.print("\t");
			}

			System.out.println("\n");
		}
	}

	public void random(ArrayList<String> population) {
		int size = getSize(population.size());		

		display("RANDOM SAMPLE", random(population, size));
	}

	public ArrayList<String> random(ArrayList<String> population, int size) {
		if(size <= 1)
			return population;

		ArrayList<String> randomSample = new ArrayList<String>();
		ArrayList<Integer> randomIndex = new ArrayList<Integer>();

		for(int i = 0; i < size; i ++) {
			int index = rand.nextInt(population.size() - 1);

			while(randomIndex.contains(index)) {
				index = rand.nextInt(population.size() - 1);
			}

			randomIndex.add(index);
		}

		for(int i = 0; i < size; i ++) {
			randomSample.add(population.get(randomIndex.get(i)));
		}

		return randomSample;
	}

	public void systematic(ArrayList<String> population) {
		int size = getSize(population.size());
		ArrayList<String> systemSample = new ArrayList<String>();

		if(size < 1)
			display("RANDOM SAMPLE (Systematic Sampling)", systemSample);

		else {
			int k = population.size() / size;
			int start = (k > 1) ? rand.nextInt(k - 1):0;

			for(int i = 0; i < size; i ++) {
				systemSample.add(population.get(start));
				start = (((i + 1) * k) % population.size());
			}

			display("RANDOM SAMPLE (Systematic Sampling)", systemSample);
		}
	}

	public void stratified(ArrayList<String> population) {
		ArrayList<ArrayList<String>> list = new ArrayList<ArrayList<String>>();

		if(dataType == 1){
			ArrayList<String> primes = new ArrayList<String>();
			ArrayList<String> odds = new ArrayList<String>();
			ArrayList<String> evens = new ArrayList<String>();

			for(int i = 0; i < population.size(); i ++) {
				if(isPrime(Integer.parseInt(population.get(i))))
					primes.add(population.get(i));
				else if(Integer.parseInt(population.get(i)) % 2 == 0)
					evens.add(population.get(i));
				else
					odds.add(population.get(i));
			}

			int index = 1;

			if(!primes.isEmpty()) {
				list.add(primes);
				display("STRATA " + index++, primes);
			}
			if(!odds.isEmpty()) {
				list.add(odds);
				display("STRATA " + index++, odds);
			}
			if(!evens.isEmpty()) {
				list.add(evens);
				display("STRATA " + index++, evens);
			}
		}
			
		else if(dataType == 2) {
			ArrayList<String> aToE = new ArrayList<String>();
			ArrayList<String> fToJ = new ArrayList<String>();
			ArrayList<String> kToO = new ArrayList<String>();
			ArrayList<String> pToT = new ArrayList<String>();
			ArrayList<String> uToZ = new ArrayList<String>();

			for(int i = 0; i < population.size(); i ++) {
				char c = population.get(i).charAt(0);

				if((c >= 'A' && c <= 'E') || (c >= 'a' && c <= 'e'))
					aToE.add(population.get(i));
				else if((c >= 'F' && c <= 'J') || (c >= 'f' && c <= 'j'))
					fToJ.add(population.get(i));
				else if((c >= 'K' && c <= 'O') || (c >= 'k' && c <= 'o'))
					kToO.add(population.get(i));
				else if((c >= 'P' && c <= 'T') || (c >= 'p' && c <= 't'))
					pToT.add(population.get(i));
				else
					uToZ.add(population.get(i));
			}

			int index = 1;

			if(!aToE.isEmpty()) {
				list.add(aToE);
				display("STRATA " + index++, aToE);
			}
			if(!fToJ.isEmpty()) {
				list.add(fToJ);
				display("STRATA " + index++, fToJ);
			}
			if(!kToO.isEmpty()) {
				list.add(kToO);
				display("STRATA " + index++, kToO);
			}
			if(!pToT.isEmpty()) {
				list.add(pToT);
				display("STRATA " + index++, pToT);
			}
			if(!uToZ.isEmpty()) {
				list.add(uToZ);
				display("STRATA " + index++, uToZ);
			}
		}

		else
			System.out.println("\n\t\tInvalid Data");

		double percent = 0;

		try {
			do {
				System.out.print("\n\t\tEnter percentage per stratum: ");

				percent = scanner.nextDouble();

				if(percent <= 0 || percent >= 100)
					System.out.println("\t\tInvalid percentage!");

			} while(percent <= 0 || percent >= 100);

			for(int i = 0; i < list.size(); i ++) {
				int size = (int)Math.ceil(list.get(i).size() * (percent / 100));
				display("STRATA " + (i+1) + " (" + size + ")", random(list.get(i), size));
			}
		} catch(java.util.InputMismatchException e) {
			System.out.println("\t\tNot an integer");
		}
	}

	private int getDataType(String data) {
		char c = data.charAt(0);
		int type = 0;

		if(c >= '0' && c <= '9') 
			type = 1;		//Integer
		else if((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z'))
			type = 2;		//Characters

		for(int i = 1; i < data.length(); i ++) {
			c = data.charAt(i);
			
			if(type == 1) {
				if(c < '0' || c > '9')
					return 0;
			} else if(type == 2) {
				if(c < 'A' || (c > 'Z' && c < 'a') || c > 'z')
					return 0;
			}
		}

		dataType = type;
		return type;
	}

	private void initArray(int size, ArrayList<String> array) {
		for(int i = 0; i < size; i ++) {
			array.add("");
		}
	}

	private boolean validate(String data) {
		for(int i = 0; i < data.length(); i ++) {
			char c = data.charAt(i);
			
			if(dataType == 1) {
				if(c < '0' || c > '9')
					return false;
			} else if(dataType == 2) {
				if(c < 'A' || (c > 'Z' && c < 'a') || c > 'z')
					return false;
			}
		}

		return true;
	}

	public int getSize(int popSize) {
		if(popSize == 1)
			return 1;

		int size = 0;

		try {
		
			do {
				System.out.print("\n\t\tEnter sample size (0 for default 20%): ");

				size = scanner.nextInt();

				if(size < 0 || size >= popSize)
					System.out.println("\t\tInvalid size!");

				if(size == 0)
					size = (int)Math.ceil(popSize * .2);

			} while(size < 0 || size >= popSize);
		} catch(java.util.InputMismatchException e) {
			System.out.println("\t\tNot an integer");
		}

		return size;
	}

	private boolean isPrime(int n) {
	    if (n%2==0 && n != 2 && n == 1) return false;
	    //if not, then just check the odds
	    for(int i=3;i*i<=n;i+=2) {
    	    if(n%i==0)
    	        return false;
    	}
    	return true;
	}
}