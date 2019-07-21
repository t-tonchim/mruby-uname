# mruby-uname   [![Build Status](https://travis-ci.org/t-tonchim/mruby-uname.svg?branch=master)](https://travis-ci.org/t-tonchim/mruby-uname)
Uname class
## install by mrbgems
- add conf.gem line to `build_config.rb`

```ruby
MRuby::Build.new do |conf|

    # ... (snip) ...

    conf.gem :github => 't-tonchim/mruby-uname'
end
```
## example
```ruby
p Uname.hi
#=> "hi!!"
t = Uname.new "hello"
p t.hello
#=> "hello"
p t.bye
#=> "hello bye"
```

## License
under the MIT License:
- see LICENSE file
