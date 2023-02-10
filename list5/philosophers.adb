--  gnatmake philosophers.adb && rm *.ali *.o
with Ada.Text_IO; use ADA.Text_IO;
with Ada.Integer_Text_IO; use Ada.Integer_Text_IO;
with Ada.Command_Line;
with Ada.Strings;
with Ada.Numerics.Float_Random;  use Ada.Numerics.Float_Random;

procedure DiningPhilosophers is
  -- Get number of philosophers and meals from command line
  no_philosophers : Integer := Integer'Value(Ada.Command_Line.Argument(1));
  no_meals        : Integer := Integer'Value(Ada.Command_Line.Argument(2));
  name            : String  := "Philosopher";

  protected type Mutex is 
    entry Seize;
    procedure Release;
  private
    Owned : Boolean := False;
  end Mutex;

  protected body Mutex is
    entry Seize when not Owned is
    begin
      Owned := True;
    end Seize;

    procedure Release is
    begin
      Owned := False;
    end Release;
  end Mutex;

  -- Create all mutexes
  type Mutex_Access is access Mutex; 
  type Mutex_Array is array (Integer range <>) of Mutex_Access;
  Mutexes : Mutex_Array(1 .. no_philosophers) := (others => new Mutex);

  -- Random float generator
  Gen : Generator;

  -- Global variable for philosopher id
  Philosopher_Id : Integer := 1;

  -- Main task
  task type Philosopher;
  task body Philosopher is
    Id    : Integer;
    Left  : Mutex_Access;
    Right : Mutex_Access;
  begin
    Reset (Gen);
    Id := Philosopher_Id;
    Philosopher_Id := Philosopher_Id + 1;

    if Id = 1 then -- Make one philosopher left-handed
      Left  := Mutexes ((Id - 1) mod no_philosophers + 1);
      Right := Mutexes ((Id) mod no_philosophers + 1);
    else -- right-handed
      Left  := Mutexes ((Id) mod no_philosophers + 1);
      Right := Mutexes ((Id - 1) mod no_philosophers + 1);
    end if;
    
    Put_Line ("[Philosopher" & Integer'Image(Id) & "] has joined the table:)");
    for I in 1 .. no_meals loop
      Left.Seize;
      Put_Line ("[Philosopher" & Integer'Image(Id) & "] has picked up left fork");

      Right.Seize;
      Put_Line ("[Philosopher" & Integer'Image(Id) & "] has picked up right fork");

      Put_Line ("[Philosopher" & Integer'Image(Id) & "] is eating om nom nom");
      delay Duration (Random (Gen) * 0.1);

      Put_Line ("[Philosopher" & Integer'Image(Id) & "] has put down right fork");
      Left.Release;

      Put_Line ("[Philosopher" & Integer'Image(Id) & "] has put down left fork");
      Right.Release;

      Put_Line ("[Philosopher" & Integer'Image(Id) & "] is thinking about the weather");
      delay Duration (Random (Gen) * 0.1);
    end loop;
    Put_Line ("[Philosopher" & Integer'Image(Id) & "] leaves the table");
  end Philosopher;

  -- Declare and run tasks
  type task_array is array (Integer range <>) of Philosopher;
  Philosophers : task_array(1 .. no_philosophers);
begin
  null;
end DiningPhilosophers;
