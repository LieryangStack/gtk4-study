# lib_src2md.rb
require 'fileutils'
require 'pathname'
include Math
include FileUtils

# The method 'src2md' converts .src.md file into .md file.
# The .md file is the final format for GFM, or intermediate markdown file for html and/or latex.
# - Links to relative URL are removed for latex. Otherwise, it remains.
#   See "Hyperref and relative link" below for further explanation.
# - Width and height for images are removed for markdown and html. it remains for latex.
#    ![sample](sample_image){width=10cm height=5cm} => ![sample](sample_image)    for markdown and html

# ---- Hyperref and relative link ----
# Hyperref package makes internal link possible.
# The target of the link is made with '\hypertarget' command.
# And the link is made with '\hyperlink' command.
# For example,
#  (sec11.tex)
#   \hyperlink{tfeapplication.c}{Section 13}
#   ... ...
#  (sec13.tex)
#   \hypertarget{tfeapplication.c}{%
#   \section{tfeapplication.c}\label{tfeapplication.c}}
# If you click on the text 'Section 13' in sec11.tex, then you will move to 'tfeapplication.c' in sec13.tex.

# The following lines are the original one in sec11.md and the result in sec11.tex, which is generated by pandoc.
#  (sec11.md)
#   All the source files are listed in [Section 13](sec13.tex).
#  (sec11.tex)
#   All the source files are listed in \href{sec13.tex}{Section 13}.
# Therefore, if you want to correct the link in sec11.tex, you need to do the followings.
# 1. Look at the first line of sec13.md and get the section heading (tfeapplication.c).
# 2. substitute "\hyperlink{tfeapplication.c}{Section 13}" for "\href{sec13.tex}{Section 13}".

# The following lines are another conversion case by pandoc.
#  (sec7.md)
#   The source code of `tfe3.c` is stored in [src/tfe](../src/tfe) directory.
#  (sec7.tex)
#   The source code of \texttt{tfe3.c} is stored in \href{../src/tfe}{src/tfe} directory.
# The pdf file generated by lualatex recognizes that the link 'href{../src/tfe}' points a pdf file '../src/tfe.pdf'.
# To avoid generating such incorrect links, it is good to remove the links from the original markdown file.

# If the target is full URL, which means absolute URL begins with "http(s)", no problem happens.

# This script just remove the links if its target is relative URL and the target is latex.
# If you want to revive the link with relative URL, refer the description above.

# This script uses "fenced code blocks" for verbatim lines.
# It is available in GFM and pandoc's markdown but not in original markdown.
# Two characters backtick (`) and tilde (~) are possible for fences.
# This script uses tilde because info string cannot contain any backticks for the backtick code fence.
# Info string follows opening fence and it is usually a language name.

# GFM has fence code block like this.
# ~~~C
# int main (int argc, char **argv) {
# ........
# ~~~
# Then the contents are highlighted based on C language syntax.
# This script finds the language by the suffix of the file name.
# .c => C, .h => C, .rb => ruby, Rakefile, => ruby, .xml => xml, .ui => xml, .y => bison, .lex => lex, .build => meson, .md => markdown
# Makefile => makefile

# Pandoc's markdown is a bit different.
# ~~~{.C .numberLines}
# int main (int argc, char **argv) {
# ........
# ~~~
# Then the contents are highlighted based on C language syntax and line numbers are added.
# Pandoc supports C, ruby, xml, bison, lex, markdown and makefile languages, but doesn't meson.
#
# After a markdown file is converted to a latex file, listings package is used by lualatex.
# Listings package supports only C, ruby, xml and make.
# Bison, lex, markdown and meson aren't supported.

# file_table contains paths of srcmd, GFM, html and latex.
# Example: [ [src/sec1.src.md, gfm/sec1.md, html/sec1.html and latex/sec1.tex], [src/sec2/src.md .....] .... ]
# If the paths are relative, srcmd and md must be relative.
# And their base directory must be the same.

# type is "gfm", "html" or "latex".
# Caller can specify the target type.

# select lines match to the type from @@@if-elif-else-end
class String
  def partitions pattern
    a = []
    b = self.partition(pattern)
    until b[1] == ""
      a += [b[0],b[1]]
      b = b[2].partition(pattern)
    end
    a += [b[0]]
  end
end

def src2md src_path, type
  dst_dir = {"gfm"=>"gfm","html"=>"docs","latex"=>"latex"}[type]
  dst_path = "#{dst_dir}/#{File.basename(src_path, ".src.md")}.md"
  src_dir = File.dirname src_path
  src = File.read(src_path)
  src = at_if_else(src, type)
  buf = src.partitions(/^@@@table\n.*?@@@\n/m)
  src = buf.map{|chunk| chunk=~/\A@@@table/ ? at_table(chunk) : chunk}.join
  buf = src.partitions(/^@@@include\s*(-(N|n))?.*?@@@\n/m)
  src = buf.map{|chunk| chunk=~/\A@@@include/ ? at_include(chunk, src_dir, type) : chunk}.join
  buf = src.partitions(/^@@@shell.*?@@@\n/m)
  src = buf.map{|chunk| chunk=~/\A@@@shell.*?@@@\n/m ? at_shell(chunk, src_dir) : chunk}.join
  src = change_link(src, src_dir, type, dst_dir)
  mkdir_p(dst_dir) unless Dir.exist?(dst_dir)
  File.write(dst_path, src)
end

# @@@if - @@@elif - @@@else - @@@end
def at_if_else str, type
  buf = str.each_line.to_a
  obuf = []
  if_stat = 0
  buf.each do |line|
    if line =~ /^@@@if *(\w+)/ && if_stat == 0
      if_stat = (type == $1 ? 1 : -1)
    elsif line =~ /^@@@elif *(\w+)/
      if if_stat == 1
        if_stat = -2
      elsif if_stat == -1
        if_stat = (type == $1 ? 3 : -3)
      elsif if_stat == -2
        # if_stat is kept to be -2
      elsif if_stat == 3
        if_stat = -2
      elsif if_stat == -3
        if_stat = (type == $1 ? 3 : -3)
      end
    elsif line =~ /^@@@else/
      if if_stat == 1
        if_stat = -2
      elsif if_stat == -1
        if_stat = 2
      elsif if_stat == -2
        # if_stat is kept to be -2
      elsif if_stat == 3
        if_stat = -2
      elsif if_stat == -3
        if_stat = 2
      end
    elsif line =~ /^@@@end/
      if_stat = 0
    elsif if_stat >= 0
      obuf << line
    end
  end
  obuf.join
end

def get_alignments(separator)
  separator = separator.sub(/^\|/,'').sub(/\|$/,'')
  separator.split('|').map{|cell| cell.lstrip.rstrip.squeeze}\
    .map do |cell|
      case cell
      when '-',':-' then :l
      when '-:' then :r
      when ':-:' then :c
      else nil
      end
    end
end

def mkcell(cell, alignment, width)
  return cell if (l = cell.length) >= width
  sp_l = (width - l) / 2
  sp_r = width - l - sp_l
  case alignment
  when :l then cell+" "*(sp_l+sp_r)
  when :r then " "*(sp_l+sp_r)+cell
  when :c then " "*sp_l+cell+" "*sp_r
  else cell
  end
end

def mksep(alignments, widths)
  seps = (0...alignments.size).map do |i|
    case alignments[i]
    when :l then ':'+'-'*(widths[i]-1)
    when :r then '-'*(widths[i]-1)+':'
    when :c then ':'+'-'*(widths[i]-2)+':'
    else ':'+'-'*(widths[i]-1)
    end
  end
  '|' + seps.join('|') + '|'
end

def at_table src
  lines = src.each_line.to_a
  lines.delete_at(0); lines.delete_at(-1)
  return lines.join unless lines[1] =~ /^\|(:?-+:?\|)+$/ && lines.map{|line| line.count('|')}.uniq.size == 1
  alignments = get_alignments(lines[1])
  a_widths = alignments.map{|alignment| alignment == :c ? 3 : 2}
  lines.delete_at(1)
  array_of_cells = lines.map{|line| line.sub(/^\|/,'').sub(/\|$/,'').split('|').map{|cell| cell.lstrip.rstrip}}
  widths = array_of_cells.inject(a_widths){|cells1, cells2| (0...cells1.size).map{|i| [cells1[i],cells2[i].length].max}}
  lines = array_of_cells.map do |cells|
   '|' + (0...cells.size).map{|i| mkcell(cells[i], alignments[i], widths[i])}.join('|') + '|'
  end
  separator = mksep(alignments, widths)
  lines.insert(1,separator)
  lines.map{|line| line+"\n"}.join
end

def width n
  return nil if n < 0
  log10(n.to_f).to_i+1
end

# @@@include -(N|n|) - @@@
def at_include str, src_dir, type
  buf = str.each_line.to_a
  opt = buf[0].match(/^@@@include\s*(-(N|n))?\s*$/).to_a[1]
  buf.delete_at(0); buf.delete_at(-1)
  obuf = []
  buf.each do |line|
    file_func = line.chomp.split(/\s/).reject{|a| a == ""}
    language = lang(file_func[0], type)
    next unless File.file?("#{src_dir}/#{file_func[0]}")
    src = File.read("#{src_dir}/#{file_func[0]}")
    if language == "C"
      if file_func.size >= 2
        a = []
        (1..file_func.size-1).each do |i|
          func_match_data = src.match(/(.*\n#{file_func[i]}\s*\(.*?\)\s*\{\s*\n(.|\n)*?^\}\s*?\n?)/)
          a << func_match_data[0] unless func_match_data == nil # func_match_data.to_s is OK, too.
        end
        src = a.join("\n")
      end
    end
    i = 0; src_lines = src.each_line.to_a; w = width(src_lines.size)
    src_with_number = src_lines.map{|l| i+=1; sprintf("%#{w}d ", i)+l}.join
    dst = "" # declare here because of the scope of local variables.
    if type == "gfm"
      unless opt == "-N"
        dst = "~~~#{language}\n#{src_with_number}~~~\n"
      else
        dst = "~~~#{language}\n#{src}~~~\n"
      end
    elsif type == "html" || type == "latex"
      unless opt == "-N"
        if language == ""
          dst = "~~~{.numberLines}\n#{src}~~~\n"
        else
          dst = "~~~{.#{language} .numberLines}\n#{src}~~~\n"
        end
      else
        if language == ""
          dst = "~~~\n#{src}~~~\n"
        else
          dst = "~~~{.#{language}}\n#{src}~~~\n"
        end
      end
    end
    obuf << dst
  end
  obuf.join
end

# @@@shell - @@@
def at_shell str, src_dir
  buf = str.each_line.to_a
  buf.delete_at(0); buf.delete_at(-1)
  obuf = ["~~~\n"]
  buf.each do |line|
    obuf << "$ #{line}"
    `cd #{src_dir}; #{line.chomp}`.each_line {|l| obuf << l}
  end
  obuf << "~~~\n"
  obuf.join
end

# Change relative links in the secXX.src.md to the one in gfm/secXX.md, html/secXX.html or latex/secXX.tex
# Example:
#  src=>gfm:  [Section 1](sec1.src.md) => [Section 1](sec1.md)
#  src=>html:  [Section 1](sec1.src.md) => [Section 1](sec1.html)
#  src=>latex:  [Section 1](sec1.src.md) => Section 1
#  src=>gfm:  [document](../doc/document.md) => [document](document.md)
#  src=>html:  [document](../doc/document.md) => [document]document.html
#  src=>latex:  [document](../doc/document.md) => document
#  src=>latex:  [Github](https://github.com/ToshioCP) => [Github](https://github.com/ToshioCP)
# The examples above are simple. But some source files are located in the different directories.
#  src/abstract.src.md => ./Readme.md: [Section 1](src/sec1.src.md) => [Section 1](gfm/sec1.md).
#  src/abstract.src.md => html/index.md: [Section 1](src/sec1.src.md) => [Section 1](sec1.html).
#  src/abstract.src.md => latex/abstract.md: [Section 1](src/sec1.src.md) => Section 1
#  src/turtle/turtle_doc.src.md => src/turtle/turtle_doc.md: [Section 1](../sec1.src.md) => [Section 1](../../gfm/sec1.md)
#  src/turtle/turtle_doc.src.md => gfm/turtle_doc.md: [Section 1](../sec1.src.md) => [Section 1](sec1.md)

# src: String
# old_dir: the directory which 'src' (XXXX.src.md) comes from
# type: 'gfm', 'html' or 'latex'.
# new_dir: the directory which the converted string put into
#   new_dir is usually gfm, html or latex. But abstract.src.md is an exception. It goes to the top directory.
#   src/turtle/turtle_doc.src.md has two possibilities.
#   It goes to src/turtle/turtle_doc.md or gfm/turtle_doc.md.
def change_link src, old_dir, type, new_dir=nil
  raise "Illegal type." unless type == "gfm" || type == "html" || type == "latex"
  new_dir = type if new_dir == nil
  p_new_dir = Pathname.new(new_dir)
  buf = src.partitions(/^~~~.*?^~~~\n/m)
  buf = buf.map{|chunk| chunk =~ /\A~~~.*?^~~~\n\z/m ? chunk : chunk.partitions(/(^    .*\n)+/)}.flatten
  # buf = buf.inject([]){|b,e| b.append(*e)}
  buf = buf.map do |chunk|
    if (chunk =~ /\A~~~.*?^~~~\n\z/m || chunk =~ /\A(^    .*\n)+\z/)
      chunk
    else
      # change inline codes (`...`) to escape char ("\e"=0x1B) in the link change procedure temporarily.
      # This avoids the influence of the change in the inline codes.
      # So, .src.md files must not include escape code (0x1B).
      codes = chunk.scan(/`.*?`/)
      chunk = chunk.gsub(/`.*?`/,"\e")
      b = chunk.partitions(/!?\[.*?\]\(.*?\)(\{.*?\})?/)
      b = b.map do |c|
        m = c.match(/(!?\[.*?\])\((.*?)\)(\{.*?\})?/)
        if m == nil
          c
        else
          name = m[1]
          target = m[2]
          size = m[3]
          if target.include?("\e")
            c
          elsif target =~ /\.src\.md$/
            case type
            when "gfm"
              "#{name}(#{File.basename(target).sub(/\.src\.md$/,'.md')})"
            when "html"
              "#{name}(#{File.basename(target).sub(/\.src\.md$/,'.html')})"
            when "latex"
              name.match(/!?\[(.*?)\]/)[1]
            end
          elsif target =~ /^(http|\/)/
            c
          elsif name =~ /^!/ # link to an image file
            n_target = Pathname.new("#{old_dir}/#{target}").relative_path_from(p_new_dir).to_s
            b_target = File.basename(target)
            case type
            when "gfm"
              "#{name}(#{n_target})"
            when "html"
              "#{name}(image/#{b_target})"
            when "latex"
              size ? "#{name}(#{n_target})#{size}" : "#{name}(#{target})"
            end
          else
            n_target = Pathname.new("#{old_dir}/#{target}").relative_path_from(p_new_dir).to_s
            if type == "gfm"
              "#{name}(#{n_target})"
            else # remove link
              name.match(/\[(.*?)\]/)[1]
            end
          end
        end
      end
      c = b.join
      a = c.split("\e")
      i = 0
      codes.inject([a[0]]){|b, code| i+=1; b.append(code, a[i])}.join
    end
  end
  buf.join
end

# Color fence code.
# See gfm => GFM document
#     html => pandoc document
#     latex => listings package
def lang file, type
  tbl = {
    "gfm.c" => "C",
    "html.c" => "C",
    "latex.c" => "C",
    "gfm.h" => "C",
    "html.h" => "C",
    "latex.h" => "C",
    "gfm.rb" => "ruby",
    "html.rb" => "ruby",
    "latex.rb" => "ruby",
    "gfm.xml" => "xml",
    "html.xml" => "xml",
    "latex.xml" => "xml",
    "gfm.ui" => "xml",
    "html.ui" => "xml",
    "latex.ui" => "xml",
    "gfm.y" => "bison",
    "html.y" => "bison",
    "latex.y" => "",
    "gfm.lex" => "lex",
    "html.lex" => "lex",
    "latex.lex" => "",
    "gfm.build" => "meson",
    "html.build" => "",
    "latex.build" => "",
    "gfm.md" => "markdown",
    "html.md" => "markdown",
    "latex.md" => "",
    "gfm.Makefile" => "makefile",
    "html.Makefile" => "makefile",
    "latex.Makefile" => "makefile",
    "gfm.Rakefile" => "ruby",
    "html.Rakefile" => "ruby",
    "latex.Rakefile" => "ruby",
   }
  name = File.basename file
  if name == "Makefile" || name == "Rakefile"
    suffix = ".#{name}"
  elsif name =~ /\.src\.md$/
    suffix = ".src.md"
  else
    suffix = File.extname name
  end
  tbl["#{type}#{suffix}"].to_s
end
