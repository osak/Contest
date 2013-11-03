#!/usr/bin/env ruby

require 'nokogiri'
require 'open-uri'
require 'fileutils'

probno = ARGV[0].to_i

doc = Nokogiri::HTML(open("http://poj.org/problem?id=#{probno}"))
title = doc.css("div.ptt")[0].content

filename = sprintf("%04d.cc", probno)
if not FileTest.exist?(filename)
  File.open(filename, 'w') do |f|
    f.puts <<TEMPLATE
//Name: #{title}
//Level:
//Category:
//Note:

#ifndef ONLINE_JUDGE
#define _GLIBCXX_DEBUG
#endif

#include <cstdio>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

#define FOREACH(it,c) for(__typeof((c).begin()) it = (c).begin(); it != (c).end(); ++it)
#define TIMES(i,n) for(int (i) = 0; (i) < (n); ++(i))

bool solve() {
}

int main() {
    while(solve()) ;
    return 0;
}
TEMPLATE
  end
end

sinput = doc.css("pre.sio")[0].content.gsub(/\r\n/, "\n")
filename = sprintf("%04d.in", probno)
File.open(filename, 'w') do |f|
  f.puts(sinput)
end
