all:
	i=1 ; while [[ $$i -le 1024 ]]; do \
		if [[ $$i -lt 512 ]]; then \
			echo -e > Foo$$i.java \
			  "public final class Foo$$i {\n" \
			  "  public int bar() {\n" \
			  "    int a = new Foo$$((i*2))().bar();\n" \
			  "    int b = new Foo$$((i*2 + 1))().bar();\n" \
			  "    return a > b ? a : b;\n" \
			  "  }\n" \
			  "}" ; \
		else \
			echo -e > Foo$$i.java \
			  "public final class Foo$$i {\n" \
			  "  public int bar() {\n" \
			  "    return $$i;\n" \
			  "  }\n" \
			  "}" ; \
		fi ; \
		(( i = i + 1 )) ; \
	done

clean:
	i=1 ; while [[ $$i -le 1024 ]]; do \ 
		rm Foo$$i.java ; \
	done
