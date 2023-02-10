/*  
  javac Main.java Philosopher.java 
  java Main
*/
class Main {
  public static void main(String[] args) {
    int no_philosophers, no_meals;
    
    try {
      no_philosophers = Integer.parseInt(args[0]); 
      no_meals = Integer.parseInt(args[1]); 
      
      if (args.length != 2) {
        System.out.println("Wrong number of arguments.");
        System.out.println("Usage: java Main <number of philosophers> <number of meals>");
      }

      if (no_meals < 1 || no_philosophers < 2) {
        System.out.println("Number of meals should be greater than 0 and number of philosophers should be greater than 1.");
        System.out.println("Usage: java Main <number of philosophers> <number of meals>");
        return;
      }

    } catch (Exception e) {
      System.out.println("Wrong parameter type.");
      System.out.println("Usage: java Main <number of philosophers> <number of meals>");
      return;
    }
 
    final Philosopher[] philosophers = new Philosopher[no_philosophers];
    Object[] forks = new Object[no_philosophers];
    for (int i = 0; i < no_philosophers; i++) 
        forks[i] = new Object();
    

    for (int i = 0; i < no_philosophers; i++) {
      Object left_fork = forks[i];
      Object right_fork = forks[(i + 1) % no_philosophers];

      if (i == 0) {
        philosophers[i] = new Philosopher(right_fork, left_fork, no_meals); 
      } else {
        philosophers[i] = new Philosopher(left_fork, right_fork, no_meals);
      }
      
      Thread t = new Thread(philosophers[i], "Philosopher" + (i + 1));
      t.start();
    }
  }
}
