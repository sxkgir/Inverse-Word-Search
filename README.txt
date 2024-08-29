HOMEWORK 7: Search Engine


NAME:  Haolie Jiang


COLLABORATORS AND OTHER RESOURCES:
List the names of everyone you talked to about this assignment
(classmates, TAs, ALAC tutors, upperclassmen, students/instructor via
LMS, etc.), and all of the resources (books, online reference
material, etc.) you consulted in completing this assignment.

stackoverflow.com
cplusplusrefrence.com

TA(kiron, etc)

Remember: Your implementation for this assignment must be done on your
own, as described in "Academic Integrity for Homework" handout.


ESTIMATE OF # OF HOURS SPENT ON THIS ASSIGNMENT:  16 hours


MISC. COMMENTS TO GRADER:
(optional, please be concise!)


## Reflection and Self Assessment

Discuss the issues you encountered during development and testing. What
problems did you have? What did you have to research and learn on your
own? What kinds of errors did you get? How did you fix them?




What parts of the assignment did you find challenging? Is there anything that
finally "clicked" for you in the process of working on this assignment? How well
did the development and testing process go for you?

I had issues of double converted into int, where the double value would not be a floating point.

The requirement to match a query word as a standalone word and not as part of another word (e.g., "Tomato" not matching "Tomatos") involved understanding how to check word boundaries. Solution: Implement logic to ensure the characters immediately before and after the query word are not alphanumeric, which indicates that the word is not part of a larger word was difficult. 

Realizing the importance of accurately checking for standalone words and the implications of integer division in C++ could have been key learning moments. These insights not only resolve immediate issues but also enrich overall understanding of programming in C++.

