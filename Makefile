ALL := AferoSofthub.zip

all: $(ALL)

clean:
	rm -f $(ALL)

AferoSofthub.zip: AferoSofthub.framework
	zip -r $@ $^

.PHONY: all clean
