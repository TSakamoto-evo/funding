1. Folder "visualize"
  R and c++ are required.

  C++ simulation is used to obtain the dynamics.

  It produces three files:
    "landscape_change.txt": it outputs the remaining significance at each grid point at that time.
    "lab_positions.txt": it outputs the position and Ai for each lab.
    "total_significance.txt": it outputs the total significance remaining in the landscape.

  R scripts are used to visualize the dynamics from the output files of c++ simulations.
  Packages "ggplot2" and "reshape2" are required.

  (how-to-use)
    1. Set appropriate parameters in "main.cpp".
    2. Compile c++ files by a following command:
      "g++ *.cpp -std=c++11 -O3 -o XXX.out"
    3. Run the simulation by a following command:
      "./XXX.out"
    4. Open on R the file "plot_landscape.R" and run it.
    5. The figure is generated in the folder "pic".

2. Folder "q_change"
  C++ are required.

  It produces a file:
    "significance_change_with_q.txt": it outputs optimal_p and its performance for each q.

  (how-to-use)
    1. Set appropriate parameters in "main.cpp".
       A parameter "reps" represents the number of replicates for each (p, q).
    2. Compile c++ files by a following command:
      "g++ *.cpp -std=c++11 -O3 -o XXX.out"
    3. Run the simulation by a following command:
      "./XXX.out"

3. Folder "three_methods"
  C++ are required.

  It produces a file:
    "significance_change_with_q.txt": it outputs optimal combination of (pc, pl)
                                      and its performance for a specified q.

  (how-to-use)
    1. Set appropriate parameters in "main.cpp".
    2. Compile c++ files by a following command:
      "g++ *.cpp -std=c++11 -O3 -o XXX.out"
    3. Run the simulation by a following command:
      "./XXX.out"

4. Folder "dynamic_landscape"
  C++ are required.

  In this simulation, a new peak of significance arise when the landscape is depleted enough.
  It produces two files:
    "significance_change_with_q.txt": it outputs optimal p and its performance for specified q.
    "significance_change_with_q_all.txt": it outputs performance at each p for a specified q.

  (how-to-use)
    1. Set appropriate parameters in "main.cpp".
    2. Compile c++ files by a following command:
      "g++ *.cpp -std=c++11 -O3 -o XXX.out"
    3. Run the simulation by a following command:
      "./XXX.out"
