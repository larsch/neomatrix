#!/usr/bin/env ruby
require 'rmagick'
img = Magick::Image.read("/home/larsch/Downloads/lemming-walking-small.gif")

palette = []
frames = []

img.each do |frame|
  data = []
  frame.export_pixels.each_slice(3) do |slice|
    rgb = slice.map { |x| x / 256 }
    index = palette.index(rgb)
    if index.nil?
      palette << rgb
      index = palette.size - 1
    end
    data << index
  end
  frame = data.each_slice(4).map { |a,b,c,d|
    (a << 6) + (b << 4) + (c << 2) + (d)
  }
  frames << frame
end


puts "static const pixel palette[] = {"
palette.each_with_index do |pal, i|
  print "  { " + pal.join(", ") + " }"
  print "," if i < palette.size - 1
  puts
end
puts "};"

puts "static const uint8_t frame[15][] = {"
frames.each_with_index do |frame, i|
  print "  { " + frame.join(", ") + " }"
  print "," if i < frames.size - 1
  puts
end
puts "};"
