# Purty colours
require 'highline/import'
begin
  require 'Win32/Console/ANSI' if RUBY_PLATFORM =~ /win32/
rescue LoadError
  raise 'You must `gem install win32console` to use color on Windows'
end

def command_echoing_output(cmd)
  escaped = cmd.gsub("'", "\\\\'")
  say "<%=color('#{escaped}', RED)%>"
  IO::popen(cmd) do |o|
    o.each { |output| print output }
  end
end

def update_subtree(subtree_dir, git_remote, git_branch = 'master', repo_root = '.')
  say "<%=color('Running git from #{repo_root}', WHITE, ON_BLUE)%>"
  Dir.chdir repo_root do |path|
    command_echoing_output "git subtree pull --squash -P #{subtree_dir} #{git_remote} #{git_branch}"
  end
end

desc "Update GLM subtree"
task :update_subtree_glm do
  update_subtree 'external/glm', 'git://github.com/g-truc/glm.git'
end

desc "Update GLM subtree"
task :update_subtree_gmgridview do
  update_subtree 'hosts/ios/external/GMGridView', 'git://github.com/gmoledina/GMGridView.git'
end
