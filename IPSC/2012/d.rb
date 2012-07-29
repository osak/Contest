#!/usr/bin/env ruby

require 'time'

class Submission
  attr_reader :time, :tis, :prob, :bytes, :hash 
  def initialize(time, tis, prob, bytes, hash)
    @time = time
    @tis = tis
    @prob = prob
    @bytes = bytes
    @hash = hash
  end
end

class Member
  attr_reader :tis, :name, :age
  def initialize(tis, name, age)
    @tis = tis
    @name = name
    @age = age
  end
end

class Team
  attr_reader :tis, :members
  attr_accessor :name, :country, :univ, :division

  class <<self
    @@teams = {}
    def get(tis)
      @@teams[tis] ||= Team.new(tis)
    end

    def each_team(&block)
      @@teams.values.each(&block)
    end
  end

  def add_member(member)
    @members << member
  end

  def each_member(&block)
    @members.each(&block)
  end

private
  def initialize(tis)
    @tis = tis
    @name = name
    @members = []
  end

end

class Problem
  attr_reader :year, :name, :authors

  class <<self
    @@problems = {}
    def get(year, name)
      tag = [year, name]
      @@problems[tag] ||= Problem.new(year, name)
    end

    def each_problem(&block)
      @@problems.values.each(&block)
    end
  end

  def add_author(name)
    @authors << name
  end

  private
  def initialize(year, name)
    @year = year
    @name = name
    @authors = []
  end
end

File.open("d-problems.txt") do |f|
  f.each_line do |line|
    year, name, author = line.chomp.split
    Problem.get(year.to_i, name).add_author(author)
  end
end

File.open("d-teams.txt") do |f|
  f.each_line do |line|
    tis, name, country, univ, div = line.chomp.split
    team = Team.get(tis)
    team.name = name
    team.country = country
    team.univ = univ
    team.division = div
  end
end

File.open("d-members.txt") do |f|
  f.each_line do |line|
    tis, name, age = line.chomp.split
    team = Team.get(tis)
    team.add_member(Member.new(tis, name, age.to_i))
  end
end

$submissions = {}
File.open("d-submissions.txt") do |f|
  f.each_line do |line|
    date, time, tis, prob, bytes, hash = line.chomp.split
    timestamp = Time.parse("#{date} #{time} GMT")
    $submissions[date] ||= []
    $submissions[date] << Submission.new(timestamp, tis, prob, bytes, hash)
  end
end

def solution(sol)
  puts sol.size
  puts sol
end

def d1
  tbl = Hash.new(0)
  $submissions.each_pair do |date, arr|
    year = date[0,4]
    tbl[year] += arr.size
  end
  solution(tbl.to_a.sort_by{|a| a[0]}.map{|a| a.join(' ')})

  tbl = Hash.new(0)
  Team.each_team do |team|
    tbl[team.country] += 1
  end
  solution(tbl.to_a.sort_by{|a| a[0]}.map{|a| a.join(' ')})

  tbl = Hash.new
  Team.each_team do |team|
    tbl[team.univ] ||= []
    tbl[team.univ] << team
  end
  res = tbl.to_a.select{|a| a[1].size>=10}.sort{|a,b| a[1].size!=b[1].size ? b[1].size<=>a[1].size : a[0]<=>b[0]}
  solution(res.map{|a| "#{a[1].size} #{a[0]}"})

  sum = 0
  teams = 0
  Team.each_team do |team|
    sum += team.members.size
    teams += 1
  end
  avg = sum.to_f / teams
  solution([sprintf("%.2f", avg)])

  tbl = Hash.new(0)
  cnt = Hash.new(0)
  Team.each_team do |team|
    div = team.division
    team.each_member do |member|
      if member.age > 0
        tbl[div] += member.age
        cnt[div] += 1
      end
    end
  end
  solution(tbl.to_a.sort.map{|a| sprintf("%s %.1f", a[0], a[1].to_f/cnt[a[0]])})

  res = []
  Problem.each_problem do |problem|
    res << "#{problem.year} #{problem.name} #{problem.authors.size}"
  end
  solution(res.sort)
end

d1
