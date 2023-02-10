import java.util.Random;

class Philosopher implements Runnable {  

  public int no_meals;

  private Object left_fork;
  private Object right_fork;

  // sleep
  private static final Random ms = new Random();
  private static final int max_waiting_time = 50;
  
  Philosopher(Object left_fork, Object right_fork, int no_meals) {
    this.left_fork = left_fork;
    this.right_fork = right_fork;
    this.no_meals = no_meals;
  }

  void sleep() { 
    try { 
      Thread.sleep(ms.nextInt(max_waiting_time)); 
    } catch (InterruptedException ex) {} 
  }

  public void run() {
    String name = Thread.currentThread().getName();
    System.out.println("[" + name + "] has joined the table:)");

    while (no_meals > 0) {
      synchronized (left_fork) {
        System.out.println("[" + name + "] has picked up left fork");
        synchronized (right_fork) {
          System.out.println("[" + name + "] has picked up right fork"); 

          System.out.println("[" + name + "] is eating om nom nom"); 
          sleep();

          System.out.println("[" + name + "] has put down right fork");
        }
        
        System.out.println("[" + name + "] has put down left fork");
      }
      System.out.println("[" + name + "] is thinking about the weather");
      sleep();

      no_meals--;
    } 
    System.out.println("[" + name + "] has left the table");
  }
}
