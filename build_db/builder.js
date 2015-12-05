var fs = require("fs");
var file = fs.readFileSync("./REF_CODE_ROME.json");
var algoliasearch = require('algoliasearch');
var client = algoliasearch("AAO34BTNP3", "31e4a978231096d0f865cf9ec722f762");
var index = client.initIndex('employment');


file = JSON.parse(file);

var pushToNeo = function(line, fiche) {
	line.ROME_PROFESSION_CARD_CODE
	line.ROME_PROFESSION_CARD_NAME
	fiche.activities
	fiche.skills
	fiche.links
	fiche.works
	fiche.plus

	
};

var getFromAlgolia = function(line, cb) {
	index.search(line.ROME_PROFESSION_CARD_CODE, function(err, content){
		console.log(content.hits[0].code);
		if (err || content.hits[0].code != line.ROME_PROFESSION_CARD_CODE){
			return cb(-1, err || "pas de match");
		else {
			pushToNeo(line, content, function(a,b){
				return cb(a, b);
			});
		}
	});
};

for (var i = 0; i < file.length; i++) {
	//console.log(file[i].ROME_PROFESSION_CARD_NAME);
	getFromAlgolia(file[i], function(a, b){
		console.log(a, b);
	});
}
