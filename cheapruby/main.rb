# usage example
#
# gtags --gtagsconf=gtags.conf --gtagslabel=user-custom
# global -xd '.*'
# global -xr '.*'
# global -xs '.*'

class Hoge
  def hello(str)
    puts(str)
  end
end

def main()
  str = 'Hello'
  i = 0
  hoge = Hoge.new
  while i < 3
    hoge.hello(str)
    i += 1
  end
end

main()
