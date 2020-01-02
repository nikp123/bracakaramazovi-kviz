#include "include/questionbank.h"

QuestionBank::QuestionBank(){
	n = "noname";
	qC = 0;
	q = static_cast<question*>(malloc(1));
	activ = static_cast<bool*>(malloc(1));
	if(!q)
		logger(ERROR, "RAM alloc at __LINE__!");
}

uint32 QuestionBank::number(void) {
	return qC;
}

bool QuestionBank::addQuestion(const std::string& text, const std::string answers[4], uint8 correct) {
	qC++;
	question *nq = static_cast<question*>(calloc(qC, sizeof(question)));
	if(!nq) {
		logger(ERROR, "RAM alloc at __LINE__!");
		return false;
	}
	memcpy(nq, q, sizeof(question)*(qC-1));
	free(q);

	bool *a = static_cast<bool*>(calloc(qC, sizeof(bool)));
	if(!a) {
		logger(ERROR, "RAM alloc at __LINE__!");
		return false;
	}
	memcpy(a, activ, sizeof(bool)*(qC-1));
	free(activ);

	nq[qC-1].text = text;
	nq[qC-1].answer[0] = answers[0];
	nq[qC-1].answer[1] = answers[1];
	nq[qC-1].answer[2] = answers[2];
	nq[qC-1].answer[3] = answers[3];
	nq[qC-1].correct = correct;

	q = nq;
	activ = a;

	return true;
}

QuestionBank::~QuestionBank() {
	n = "";
	qC = 0;
	free(q);
	delete activ;
	q = nullptr;
	activ = nullptr;
}

question* QuestionBank::getQuestion(uint32 number) {
	return &q[number];
}

bool QuestionBank::deleteQuestion(uint32 number) {
	// moving all the questions in front of it
	// one address space backwards
	for(uint32 i = number+1; i < qC; i++) {
		q[i-1] = q[i];
	}

	qC--;

	// resize
	question *nq = static_cast<question*>(calloc(qC, sizeof(question)));
	if(!nq) {
		logger(ERROR, "RAM alloc at __LINE__!");
		return false;
	}
	memcpy(nq, q, sizeof(question)*qC);
	free(q);

	q = nq;
	return true;
}

void QuestionBank::clear(void) {
	n = nullptr;
	qC = 0;
	delete q;
	delete activ;
	q = static_cast<question*>(malloc(1));
	activ = static_cast<bool*>(malloc(1));
}

bool QuestionBank::loadFromFile(std::string filename){
	FILE *f = fopen(filename.c_str(), "rb");
	if(!f) {
		logger(ERROR, "Could not open file: " + filename);
		return false;
	}

	uint8 ln = 0;
	std::string text, answers[4];
	uint8 correct = 0;
	while(1) {
		char *line = nullptr;
		size_t len = 0;

		ssize_t error = getline(&line, &len, f);
		if(error == -1) {
			if(ln) logger(WARNING, "Invalid formatting!");
			break;
		}

		// im too lazy to do this properly
		switch(ln) {
			case 0:
				text = line;
				break;
			case 1:
				if(sscanf(line ,"%hhx", &correct) == 0) {
					logger(ERROR, "Error reading file!");
					clear();
					return false;
				}
				break;
			default:
				answers[ln-2] = line;
				break;
		}
		free(line);

		// increment and update line
		ln++;
		if(ln>5) {
			ln = 0;
			if(!addQuestion(text, answers, correct)) {
				logger(ERROR, "Error allocating question!");
				clear();
				return false;
			}
		}
	}

	fclose(f);
	return true;
}

bool QuestionBank::initQuestionList(void) {
	if(!qC) return false;
	for(uint32 i=0; i<qC; i++) activ[i] = false;
	return true;
}

uint32 QuestionBank::getRandomQuestion(void) {
	uint32 random = ((int32)rand())%qC;
	uint32 i;

	// if there aren't any questions left return error
	bool any = false;
	for(i=0; i<qC; i++) {
		// shitty binary search
		if(!activ[i]) {
			any = true;
			break;
		}
	}
	if(any == false) return UINT_MAX;

	i=0;

	// avoiding while(random) because bugs
	while(random) {
		if(!activ[i]) random--;
		i++;
		if(i>=qC) i=0;
	}
	while(1) {
		if(!activ[i]) break;
		i++;
		if(i>=qC) i=0;
	}

	activ[i] = true;

	// perform shuffle magic so that i can fuck over speedrunners :D
    // link: https://en.wikipedia.org/wiki/Fisher%E2%80%93Yates_shuffle#Modern_method
	for(uint8 j=0; j<2; j++) {
		uint8 k = (((uint8)rand())%(4-j))+j;
		q[i].answer[j].swap(q[i].answer[k]);
		if(q[i].correct == j) q[i].correct = k;
		else if(q[i].correct == k) q[i].correct = j;
	}

	return i;
}
