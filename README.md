# **Sorts_C**
## **Including:**
* **Insertion Sort** + _stats_
* **Merge Sort** + _stats_
* **Quick Sort** + _stats_

Automated compilation with run.c. After compilation we can choose algorithm run options.<br>
**Options:**
* **--type** - _insert_, _merge_, _quick_ (type of sort, needed to compile)
* **--comp** - _"<="_, _">="_ (sort order, needed to compile)
* **--stat** - _filename_, _k_ (sort statistics in k tests with n*100 sized array 1<=n<=100 saved to filename, optional)

**Example:** _./run --type merge --comp "<=" --stat ./statistics/data.txt 10_
