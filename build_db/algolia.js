var algoliasearch = require('algoliasearch');
var client = algoliasearch("AAO34BTNP3", "31e4a978231096d0f865cf9ec722f762");
var index = client.initIndex('employment');

index.search(code, function(err, content){
	console.log(err, content);
});

exports.getAlgoliaCodes = function(req, cb) {
  var candidateSkills = req.body.skills;

  if (!candidateSkills || candidateSkills.length < 1)
    return cb([]);

  helper.on('result', function(data){
    var skillsProcess = {};
    for (var i = 0 ; i < data.hits.length; i++){
      if (!skillsProcess[data.hits[i].code])
        skillsProcess[data.hits[i].code] = {match:0, skillsNbr: data.hits[i].skills.length, skills: [], works: data.hits[i].works};

      for (var j = 0 ; j < data.hits[i].skills.length; j++){
        if (candidateSkills.indexOf(data.hits[i].skills[j]) != -1){
          skillsProcess[data.hits[i].code].match += 1 / data.hits[i].skills.length;
          skillsProcess[data.hits[i].code].skills.push({title:data.hits[i].skills[j], value:true});
        }
        else {
          skillsProcess[data.hits[i].code].skills.push({title:data.hits[i].skills[j], value:false});
        }
      }
    }

    var jobsArray = [];
    for (var k in skillsProcess){
        skillsProcess[k].code = k;
        jobsArray.push(skillsProcess[k]);
    }

    jobsArray = jobsArray.sort(function(a, b) {
      return b.match - a.match;
    });
    client.destroy();
    return cb(jobsArray);
  });

  for (var i = 0 ; i < candidateSkills.length; i++){
    helper.addDisjunctiveFacetRefinement('skills', candidateSkills[i]);
  }

  helper.search();
};
