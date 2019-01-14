# ssl_hash

implementation of md5, whirlpool, sha224, sha256, sha384, sha512, sha512/224, sha512/256 [hashing functions](https://en.wikipedia.org/wiki/Hash_function), with interface similar to openssl.

How to use ssl_hash:
```

./ssl_hash algo_name get_hash_of_this_file -s "and this string" and_another_file

./ssl_hash algo_name -p (read from stdin) -r (move info (file name, string), after hash) -q (write only hashes)

without arguments ssl_hash will read commands from stdin and execute them after enter in a loop, till it reads EOF.

```

How to use test:
```
./test algo_name start_len end_len

./test sha256 100 500   will create file filled with 100 random characters,
                        run openssl and mine sha256 implementations on it, and compare resulting hashes.
                        Then do the same with files of size 101, 102, 103, up to 501.
```
