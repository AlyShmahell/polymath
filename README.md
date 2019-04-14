# intf
Multiple Precision Integer Arithmetic C++ Library.  

#### Roadmap

| Feature       | Implementation                                   | Next Candidate       |
|:-------------:| ------------------------------------------------:| --------------------:|
| Constructors  | std::string, int, long int, long long int, intf  | <ul><li>- [ ] </li></ul> |
| Containers    | std::vector<<int>>                                 | std::vector<std::bitset<<int>> > |
| +             | standard                                         | <ul><li>- [ ] </li></ul> |
| -             | standard                                         | <ul><li>- [ ] </li></ul> |
| *             | Long multiplication                              | Karatsuba multiplication, Toom–Cook, Schönhage–Strassen, Fürer's algorithm, Harvey and van der Hoeven|
| /             | Approximate Division                             | Newton–Raphson, Goldschmidt, Binomial Goldschmidt, Barrett reduction, Montgomery reduction |
| %             | Approximate Division                             | Newton–Raphson, Goldschmidt, Binomial Goldschmidt, Barrett reduction, Montgomery reduction |
| pow           | standard                                         | Exponentiation by squaring |
| sqrt          | bisection                                        | Babylonian(Heron), Newton-Raphson, Goldschmidt, Bakhshali approximation, Fast inverse square root |
| modexp        | <ul><li>- [ ] </li></ul>                         | Right-to-left binary     |
| abs           | <ul><li>- [x] </li></ul>                         | <ul><li>- [ ] </li></ul> |
| >>            | repetitive approximate division                  | <ul><li>- [ ] </li></ul> |
| <<            | repetitive approximate division                  | <ul><li>- [ ] </li></ul> |
| &             | <ul><li>- [ ] </li></ul>                         | <ul><li>- [ ] </li></ul> |
| ^             | <ul><li>- [ ] </li></ul>                         | <ul><li>- [ ] </li></ul> |
| xor           | <ul><li>- [ ] </li></ul>                         | <ul><li>- [ ] </li></ul> |
| ostream>>     | <ul><li>- [x] </li></ul>                         | <ul><li>- [ ] </li></ul> |
| ostream<<     | <ul><li>- [x] </li></ul>                         | <ul><li>- [ ] </li></ul> |  

#### Next Steps:  
- Code Refactoring
- Templating
- Impmementing Next Feature Candidates
- Implementing Missing Features