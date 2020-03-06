const glm::dquat PathSegment::piecewiseSquadRotation(double t) const {
  
    // breakpoints for subintervals
    const double t1 = 0.1;
    const double t2 = 0.3; // TODO: these should probably be based on distance
    const double t3 = 0.7;
    const double t4 = 0.9; 

    // TODO: validate t's?

    glm::dvec3 startNodePos = sceneGraphNode(_start.referenceNode)->worldPosition();
    glm::dvec3 endNodePos = sceneGraphNode(_end.referenceNode)->worldPosition();

    glm::dvec3 startUpVec = _start.rotation * glm::dvec3(0.0, 1.0, 0.0);
    glm::dvec3 endUpVec = _end.rotation * glm::dvec3(0.0, 1.0, 0.0);

    glm::dquat lookAtStartQ1 = helpers::getLookAtQuaternion(getPositionAt(t1), startNodePos, startUpVec);
    glm::dquat lookAtStartQ2 = helpers::getLookAtQuaternion(getPositionAt(t2), startNodePos, startUpVec);
    glm::dquat lookAtEndQ1 = helpers::getLookAtQuaternion(getPositionAt(t3), endNodePos, endUpVec);
    glm::dquat lookAtEndQ2 = helpers::getLookAtQuaternion(getPositionAt(t4), endNodePos, endUpVec);

    std::vector<glm::dquat> keyframes{ 
        _start.rotation, 
        lookAtStartQ1, 
        lookAtStartQ2,
        lookAtEndQ1,
        lookAtEndQ2, 
        _end.rotation 
    };

    std::vector<double> times{ 0.0, t1, t2, t3, t4, 1.0 };

    // Interpolate keyframes using SQUAD [Shoemake 1987]

    // TODO: test times.length == keyframes.length

    glm::dquat result;
    glm::dquat q_prev, q, q_inv, q_next, log1, log2, s1, s2;
    int nrSegments = keyframes.size() - 1;
    int lastIndex = nrSegments - 1;

    // Find the current segment and compute interpolation
    for (int i = 0; i < nrSegments; ++i) {
        if (t <= times[i + 1]) {
            // Compute S1
            q_prev = (i == 0) ? keyframes.front() : keyframes[i - 1];
            q = keyframes[i];
            q_inv = glm::inverse(keyframes[i]);
            q_next = keyframes[i + 1];

            log1 = glm::log(q_inv * q_next);
            log2 = glm::log(q_inv * q_prev);

            s1 = q * glm::exp((-1.0 / 4.0) * (log1 + log2));

            // Compute S2
            int j = i + 1;
            q_prev = keyframes[j - 1];
            q = keyframes[j];
            q_inv = glm::inverse(keyframes[j]);
            q_next = (i == lastIndex) ? keyframes.back() : keyframes[j + 1];

            log1 = glm::log(q_inv * q_next);
            log2 = glm::log(q_inv * q_prev);

            s2 = q * glm::exp((-1.0 / 4.0) * (log1 + log2));

            double tScaled = (t - times[i]) / (times[i + 1] - times[i]);
            result = glm::squad(keyframes[i], keyframes[i + 1], s1, s2, tScaled);
            break;
        }
    }

    return result;

}