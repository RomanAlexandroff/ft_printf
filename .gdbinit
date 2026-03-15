
# prevents output from pausing
set pagination off
# remove confirmation prompts
set confirm off
# formats structs nicely
set print pretty on
# remove limit to output elements
set print elements 0
# always show memory addresses
set print address on
# save my command history (like in Terminal)
set history save on

# SCRIPT: MAKE GDB SHOW 5 LINES OF CODE PER STEP like LLDB
set listsize 5
define hook-stop
python
import gdb
f = gdb.selected_frame()
sal = f.find_sal()
ln = sal.line
file = sal.symtab.fullname()
start = ln - 2
end = ln + 2
lines = gdb.execute(f"list {start},{end}", to_string=True)
for line in lines.splitlines():
    if line.lstrip().startswith(str(ln)):
        print(">" + line)
    else:
        print(" " + line)
end
end
# END OF THE SCRIPT =======================================